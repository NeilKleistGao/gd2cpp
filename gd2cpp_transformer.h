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
#include "modules/gdscript/gdscript_parser.h"

class GD2CPPTransformer: public Object {
  GDCLASS(GD2CPPTransformer, Object);
public:
  GD2CPPTransformer();
  ~GD2CPPTransformer();
  static GD2CPPTransformer* get_singleton();
  static void release();

  String transform(const String& p_path, const String& p_code, Error* p_err);
private:
  static GD2CPPTransformer* singleton;

  GDScriptParser* parser;
  Error* err;
};

#endif

#endif // __GD2CPP__TRANSFORMER__H__
