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

#include "gd2cpp_transformer.h"

#ifdef TOOLS_ENABLED
GD2CPPTransformer* GD2CPPTransformer::singleton = nullptr;

GD2CPPTransformer* GD2CPPTransformer::get_singleton() {
  if (singleton == nullptr) {
    singleton = memnew(GD2CPPTransformer);
  }

  return singleton;
}

void GD2CPPTransformer::release() {
  if (singleton != nullptr) {
    memdelete(singleton);
  }
}

String GD2CPPTransformer::transform(const String& p_path, const String& p_code, Error* p_err) {
  err = p_err;
  *err = parser->parse(p_code, p_path, false);
  if (*err != OK) {
    print_error("can not compile " + p_path);
  }

  // TODO: translate

  return "";
}

GD2CPPTransformer::GD2CPPTransformer() {
  parser = memnew(GDScriptParser);
}

GD2CPPTransformer::~GD2CPPTransformer() {
  memdelete(parser);
}

#endif
