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

#ifndef __GD2CPP_AST_H__
#define __GD2CPP_AST_H__

#ifdef TOOLS_ENABLED
#include "modules/gdscript/gdscript_parser.h"

#define USE(__CLASSNAME__)\
using __CLASSNAME__ = GDScriptParser::__CLASSNAME__

namespace gd2cpp {
  namespace gdast {
    USE(ClassNode);
  } // namespace gdast

  namespace cppast {
    class Node {
    private:
    protected:
    public:
      virtual ~Node() = default;
      virtual String to_string() = 0;
    };

    class Class: public Node {
    private:
    protected:
    public:
      virtual ~Class() override = default;
      String to_string() final;
    };

    class Program: public Node {
    private:
      const String header_comment;
      Class* main_class;
    protected:
    public:
      virtual ~Program() override;
      String to_string() final;
      static Program* create(Class* p_cls);

      Program();
    };
  } // namespace cppast
} // namespace gd2cpp

#undef USE
#endif

#endif // __GD2CPP_AST_H__
