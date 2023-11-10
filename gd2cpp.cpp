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
#include "gd2cpp_db.h"

namespace gd2cpp {
  namespace {
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

    void compile(const String& p_from, const String& p_dir) {
      Error err;
      Ref<FileAccess> file = FileAccess::open(p_from, FileAccess::READ, &err);
      if (err != OK) {
        print_error("Cannot read file " + p_from + ".");
      }
      else {
        String to = p_from.replace("res://", String{"res://"} + p_dir + "/").replace(".gd", "");
        cppast::Program* res = GD2CppTransformer::get_singleton()->transform(p_from, to, file->get_as_utf8_string(), &err);
        
        res->save();
        memdelete(res);
      }
    }
  } // namespace

  void run(GD2CppDialog* p_diag) {
    int progress = 0;
    print_line("Scanning project...");

    Array scripts = scan();
    print_line(String{"Got "} + String::num_int64(scripts.size()) + String{" script(s)."});
    ++progress;

    const String output_path = ProjectSettings::get_singleton()->get_setting("gd2cpp/directory", "native");
    for (int i = 0; i < scripts.size(); ++i) {
      const String& s = scripts[i];
      p_diag->step(String{"Translating "} + s + "...", progress);
      compile(s, output_path);
    }

    p_diag->finish();
    GD2CppTransformer::release();
    GD2CppDB::release();
  }
} // namespace gd2cpp

#endif
