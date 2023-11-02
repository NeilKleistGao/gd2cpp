/**
 * MIT License
 *
 * Copyright (c) 2023 Cunyuan(Holden) Gao 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include "gd2cpp.h"

#ifdef TOOLS_ENABLED
#include "core/variant/variant.h"
#include "core/io/dir_access.h"
#include "core/io/file_access.h"
#include "core/config/project_settings.h"

#include "gd2cpp_transformer.h"

namespace gd2cpp {
  namespace {
    static void save(const String& p_filename, const String& p_content) {
      Error err;
      const String path = p_filename.get_base_dir();
      Ref<DirAccess> dir = DirAccess::open("res://", &err);
      if (!dir->dir_exists(path)) {
        err = dir->make_dir_recursive(path);
        if (err != OK) {
          print_error("Cannot create directory " + path + ".");
          return;
        }
      }

		  Ref<FileAccess> file = FileAccess::open(p_filename, FileAccess::WRITE, &err);
      if (err != OK) {
        print_error("Cannot save LLVM file " + p_filename + ".");
      }
      else {
        file->store_string(p_content);
      }
    }

    Array scan() {
      Array scripts{}, queue{};
      queue.push_back(String{"res://"});
      Error err = Error::OK;

      while (!queue.is_empty()) {
        String cur = queue.pop_front();
        print_line(String{"Scanning "} + cur);
        Ref<DirAccess> dir = DirAccess::open(cur, &err);

        if (err != Error::OK) {
          ERR_PRINT("Failed when scanning project.");
          scripts.clear();
          break;
        }

        PackedStringArray files = dir->get_files();
        PackedStringArray dirs = dir->get_directories();

        for (int i = 0; i < files.size(); ++i) {
          String filename = files[i];
          if (filename.ends_with(".gd")) {
            String fullpath = (cur.ends_with("/")) ? cur + filename : cur + "/" + filename;
            if (scripts.find(fullpath) == -1) {
              print_line(String{"Found "} + fullpath);
              scripts.push_back(fullpath);
            }
          }
        }

        for (int i = 0; i < dirs.size(); ++i) {
          String next = dirs[i];
          queue.push_back(DirAccess::get_full_path(next, DirAccess::ACCESS_RESOURCES));
        }
      }

      return scripts;
    }

    String compile(const String& p_from, const String& p_dir) {
      String to = p_from.replace("res://", String{"res://"} + p_dir + "/").replace(".gd", ".cpp");
      Error err;
      Ref<FileAccess> file = FileAccess::open(p_from, FileAccess::READ, &err);
      if (err != OK) {
        print_error("Cannot read file " + p_from + ".");
      }
      else {
        gd2cpp::cppast::Program* res = GD2CPPTransformer::get_singleton()->transform(p_from, file->get_as_utf8_string(), &err);
        save(to, res->to_string());
        memdelete(res);
        return to;
      }

      return "";
    }
  } // namespace

  void run(GD2CppDialog* p_diag) {
    int progress = 0;
    print_line("Scanning project...");

    Array scripts = gd2cpp::scan();
    print_line(String{"Got "} + String::num_int64(scripts.size()) + String{" script(s)."});
    ++progress;

    const String output_path = ProjectSettings::get_singleton()->get_setting("gd2cpp/directory", "llvm");
    for (int i = 0; i < scripts.size(); ++i) {
      const String& s = scripts[i];
      p_diag->step(String{"Translating "} + s + "...", progress);
      String to = gd2cpp::compile(s, output_path); // TODO: store `to` for mapping
      print_line(to);
    }

    p_diag->finish();
    GD2CPPTransformer::release();
  }
} // namespace gd2cpp

#endif
