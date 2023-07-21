//
// Created by HP on 2023/7/20.
//

#ifndef GODOT_CPP_TEST_UTILS_H
#define GODOT_CPP_TEST_UTILS_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;
namespace utils {

class ControlUtils {
public:
	static Variant get_node_property(Node* node);
};

} // utils

#endif //GODOT_CPP_TEST_UTILS_H
