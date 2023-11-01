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

#ifndef __EDITOR_GD2CPP_DIALOG__H__
#define __EDITOR_GD2CPP_DIALOG__H__

#ifdef TOOLS_ENABLED
#include "scene/gui/dialogs.h"

class GD2CppDialog: public ConfirmationDialog {
  GDCLASS(GD2CppDialog, ConfirmationDialog);
public:
  GD2CppDialog();

  void ok_pressed() final;
private:
  Label* hint_text = nullptr;

  int progress = 0;
  /**
   * 0. scan scripts
   * 1. translate
   * 2. compile
   * 3. backup files
   * 4. update references
   * 5. export
   * 6. reset
  */
  const int full_steps = 7;
  static String task_name;

  void run();
};
#endif

#endif // __EDITOR_GD2CPP_DIALOG__H__

