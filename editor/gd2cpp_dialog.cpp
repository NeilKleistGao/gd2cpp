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
#include "../helper.h"

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
  singleton->progress_add_task(task_name, "Copy Project", full_steps);
  singleton->progress_task_step(task_name, "Copy Project", 0);
  run();
}

GD2CppDialog::~GD2CppDialog() {
  memdelete(hint_text);
}

void GD2CppDialog::run() {
  EditorNode* singleton = EditorNode::get_singleton();

  if (gd2cpp::copy_project() == Error::OK) {
    print_line("copied project...");
    // TODO: next
  }
  else {
    ERR_FAIL_MSG("can not copy the project.");
    // TODO: error report
  }

  progress = full_steps;
  if (progress == full_steps) {
    singleton->progress_end_task(task_name);
  }
  else {
    singleton->progress_task_step(task_name, "Copy Project", progress);
  }
}

#endif
