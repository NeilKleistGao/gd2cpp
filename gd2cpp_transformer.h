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

#ifndef __GD2CPP__TRANSFORMER__H__
#define __GD2CPP__TRANSFORMER__H__

#ifdef TOOLS_ENABLED
#include "core/object/class_db.h"
#include "core/object/object.h"

#include "gd2cpp_ast.h"
using namespace gd2cpp::gdast;

class GD2CppTransformer: public Object {
  GDCLASS(GD2CppTransformer, Object);
public:
  GD2CppTransformer();
  ~GD2CppTransformer();
  static GD2CppTransformer* get_singleton();
  static void release();

  gd2cpp::cppast::Program* transform(const String& p_from, const String& p_to, const String& p_code, Error* p_err);
private:
  static GD2CppTransformer* singleton;

  GDScriptParser* parser;
  Error* err;

  gd2cpp::cppast::Class* transform_class(ClassNode* p_node, const String& p_default_name);
};

#endif

#endif // __GD2CPP__TRANSFORMER__H__
