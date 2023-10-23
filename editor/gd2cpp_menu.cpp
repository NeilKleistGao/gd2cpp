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

#include "gd2cpp_menu.h"

#ifdef TOOLS_ENABLED


bool GD2CppMenu::inited = false;

GD2CppMenu::GD2CppMenu(): shown_title("Export with GD2Cpp") {
  if (!inited) { // TODO: do better?
    inited = true;
    add_tool_menu_item(shown_title, callable_mp(this, &GD2CppMenu::popup));
    dialog = memnew(GD2CppDialog);
    add_child(dialog);
  }
}

GD2CppMenu::~GD2CppMenu() {
  memdelete(dialog);
  dialog = nullptr;
}

String GD2CppMenu::get_name() const {
  return "GD2Cpp";
}

bool GD2CppMenu::has_main_screen() const {
  return false;
}

void GD2CppMenu::popup() {
  if (dialog != nullptr) {
    dialog->popup_centered_ratio(0.01f);
  }
}

#endif
