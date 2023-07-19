//
// Created by HP on 2023/7/19.
//

#include "godot_node_extension.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <utility>


namespace graph_extension {

void Port::_bind_methods() {
	ClassDB::bind_method(
			D_METHOD("set_value", "value"),
			&Port::set_value
	);
	ClassDB::bind_method(
			D_METHOD("get_value"),
			&Port::get_value
	);
}

Port::Port() {
	UtilityFunctions::print("hello port");
}

Port::~Port() {
	UtilityFunctions::print("goodbye port");
}

void Port::set_value(Variant p_value) {
	value = std::move(p_value);
}

Variant Port::get_value() const {
	return value;
}

void GraphEditExtension::_bind_methods() {

}

void GraphNodeExtension::_bind_methods() {

}
}//graph_extension