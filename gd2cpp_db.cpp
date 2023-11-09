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

#include "gd2cpp_db.h"

#ifndef TOOLS_ENABLE

GD2CppDB* GD2CppDB::singleton = nullptr;

GD2CppDB::GD2CppDB() {
}

GD2CppDB::~GD2CppDB() {
}

GD2CppDB* GD2CppDB::get_singleton() {
  if (singleton == nullptr) {
    singleton = memnew(GD2CppDB);
  }

  return singleton;
}

void GD2CppDB::release() {
  if (singleton != nullptr) {
    memdelete(singleton);
  }
}

bool GD2CppDB::is_godot_class(const String& p_name) {
  return p_name == "Node" || p_name == "Node2D"; // TODO: scan the folder
}

#endif
