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

#include "helper.h"

#include "editor/editor_node.h"
#include "core/config/project_settings.h"

namespace gd2cpp {
  Error copy_project() {
    EditorNode::get_singleton()->save_all_scenes();
    const String target_path = ProjectSettings::get_singleton()->has_setting("gd2cpp/path") ?
      (String)ProjectSettings::get_singleton()->get_setting("gd2cpp/path") : String("./gd2cpp");
    print_line("copying project to", target_path, "...");
    return Error::OK;
  }
} // namespace gd2cpp