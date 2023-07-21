//
// Created by HP on 2023/7/20.
//

#include "utils.h"

#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/check_button.hpp>
#include <functional>


using ControlFunction = std::function<Variant(Node*)>;

std::unordered_map<std::string, ControlFunction> control_functions = {
		{ "LineEdit", [](Node* node) {
			return Object::cast_to<LineEdit>(node)->get_text();
		}
		},
		{ "Label", [](Node* node) {
			return Object::cast_to<Label>(node)->get_text();
		}
		},
		{ "CheckButton", [](Node* node) {
			return Object::cast_to<CheckButton>(node)->is_pressed();
		}
		},
		{ "Button", [](Node* node) {
			return Object::cast_to<Button>(node)->is_pressed();
		}
		}
};


namespace utils {
Variant ControlUtils::get_node_property(Node* node) {
	if (node == nullptr) {
		return {Variant::NIL};
	}

	std::string class_name = node->get_class().utf8().get_data();
	auto it = control_functions.find(class_name);
	if (it != control_functions.end()) {
		return it->second(node);
	}

	return {Variant::NIL};
}

} // utils



