//
// Created by HP on 2023/7/19.
//

#include "test.h"

#include <godot_cpp/variant/utility_functions.hpp>


void Test::_bind_methods() {

}

void Test::_notification(int p_what) {
	switch ( p_what ) {
	case NOTIFICATION_PROCESS:
		UtilityFunctions::print("hello, ", get_name());
		break;
	}
}

void Test::_process(double delta) {
	UtilityFunctions::print("hello");
}
