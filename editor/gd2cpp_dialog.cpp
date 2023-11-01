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

#include "gd2cpp_dialog.h"

#ifdef TOOLS_ENABLED
#include "scene/gui/label.h"
#include "editor/editor_node.h"
#include "core/config/project_settings.h"
#include "../gd2cpp.h"
#include "../gd2cpp_transformer.h"

String GD2CppDialog::task_name = "gd2cpp";

GD2CppDialog::GD2CppDialog() {
  set_title(TTR("Export with GD2Cpp"));
  hint_text = memnew(Label);
  hint_text->set_text(
    "Export current project by translating gdscript to llvm IR. Only current platform is supported. Please make sure LLVM assembler is available."
  );
  add_child(hint_text);
}

void GD2CppDialog::ok_pressed() {
  EditorNode* singleton = EditorNode::get_singleton();
  singleton->progress_add_task(task_name, "Scanning project...", full_steps);
  singleton->progress_task_step(task_name, "Scanning project...", 0);
  run();
}

void GD2CppDialog::run() {
  EditorNode* singleton = EditorNode::get_singleton();
  print_line("Scanning project...");

  Array scripts = gd2cpp::scan();
  print_line(String{"Got "} + String::num_int64(scripts.size()) + String{" script(s)."});
  ++progress;

  const String output_path = ProjectSettings::get_singleton()->get_setting("gd2cpp/directory", "llvm");
  for (int i = 0; i < scripts.size(); ++i) {
    const String& s = scripts[i];
    singleton->progress_task_step(task_name, String{"Translating "} + s + "...", progress);
    String to = gd2cpp::compile(s, output_path); // TODO: store `to` for mapping
    print_line(to);
  }

  singleton->progress_end_task(task_name);
  // GD2CPPTransformer::release();
}

#endif
