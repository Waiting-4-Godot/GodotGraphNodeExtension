//
// Created by HP on 2023/7/19.
//

#include "test.h"

#include <godot_cpp/variant/utility_functions.hpp>


void Test::_bind_methods() {

}

void Test::_process(double delta) {
	UtilityFunctions::print("hello, ", get_name());
}
