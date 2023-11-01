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
// GD2CPPTransformer* GD2CPPTransformer::singleton = nullptr;

// GD2CPPTransformer* GD2CPPTransformer::get_singleton() {
//   if (singleton == nullptr) {
//     singleton = memnew(GD2CPPTransformer);
//   }

//   return singleton;
// }

// void GD2CPPTransformer::release() {
//   if (singleton != nullptr) {
//     memdelete(singleton);
//   }
// }

// String GD2CPPTransformer::transform(const String& p_path, const String& p_code, Error* p_err) {
//   err = p_err;
//   filename = p_path;
//   *err = parser->parse(p_code, p_path, false);
//   if (*err != OK) {
//     print_error("can not compile " + p_path);
//   }

//   return gen_source_filename() + "\n" + transform_root_class(parser->get_tree());
// }

// GD2CPPTransformer::GD2CPPTransformer(): err{nullptr}, filename{""} {
//   parser = memnew(GDScriptParser);
// }

// GD2CPPTransformer::~GD2CPPTransformer() {
//   if (parser != nullptr) {
//     memdelete(parser);
//     parser = nullptr;
//   }
// }

// String GD2CPPTransformer::transform_root_class(ClassNode* p_cls) {
//   String class_name = p_cls->get_global_name();
//   if (class_name.is_empty()) { // if it is empty, the name doesn't matter
//     class_name = filename.replace("/", "_").replace(".", "_").replace(":", "_");
//   }

//   String res = gen_class_name(class_name) + " = type{ ";
//   bool first = true;
//   for (auto* ext: p_cls->extends) {
//     String name = ext->name;
//     if (name.is_empty()) {
//       print_error("invalid extend name in " + class_name);
//     }
//     else {
//       if (first) {
//         first = false;
//       }
//       else {
//         res += ", ";
//       }

//       res += gen_class_name(name);
//     }
//   }

//   // TODO: members
//   res += " }\n";

//   return res;
// }

#endif
