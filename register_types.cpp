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

#include "register_types.h"

#ifdef TOOLS_ENABLED
#include "editor/gd2cpp_dialog.h"
#include "core/config/project_settings.h"
#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#endif

#ifdef TOOLS_ENABLED
class GD2CppPlugin: public EditorPlugin {
  GDCLASS(GD2CppPlugin, EditorPlugin);
private:
  GD2CppDialog* dialog;
public:
  String get_name() const override {
    return "GD2Cpp";
  }
	bool has_main_screen() const override {
    return false;
  }

  void popup() {
    dialog->popup_centered_ratio(0.01f);
  }

  GD2CppPlugin(): EditorPlugin() {
    dialog = memnew(GD2CppDialog);
    add_child(dialog);
  }
};

static GD2CppPlugin* plugin;

static void _editor_init() {
  plugin = memnew(GD2CppPlugin);
  EditorNode::get_singleton()->add_child(plugin);
  plugin->add_tool_menu_item("Export with GD2Cpp", callable_mp(plugin, &GD2CppPlugin::popup));
}
#endif

void initialize_gd2cpp_module(ModuleInitializationLevel p_level) {
#ifdef TOOLS_ENABLED
  if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
    GLOBAL_DEF_RST("gd2cpp/template", "");
    GLOBAL_DEF_RST("gd2cpp/directory", "natives");
    EditorPlugins::add_by_type<GD2CppPlugin>();
    EditorNode::add_init_callback(_editor_init);
  }
#endif
}

void uninitialize_gd2cpp_module(ModuleInitializationLevel p_level) {
}
