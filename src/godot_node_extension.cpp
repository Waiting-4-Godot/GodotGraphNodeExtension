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

void Port::set_value_changed(bool p_value_changed) {
	value_changed = p_value_changed;
}

bool Port::is_value_changed() const {
	return value_changed;
}

void GraphEditExtension::_bind_methods() {
	ClassDB::bind_method(
			D_METHOD(
					"connect_node",
					"from_node", "from_port", "to_node", "to_port"
			),
			&GraphEditExtension::connect_node
	);
	ClassDB::bind_method(
			D_METHOD(
					"disconnect_node",
					"from_node", "from_port", "to_node", "to_port"
			),
			&GraphEditExtension::disconnect_node
	);
}

Error GraphEditExtension::connect_node(const StringName& from_node, int from_port, const StringName& to_node, int to_port) {
	Error error = GraphEdit::connect_node(from_node, from_port, to_node, to_port);

	if ( error != OK ) {
		return error;
	}

	// TODO 在这里处理连接
	GraphNodeExtension* output_node = get_node<GraphNodeExtension>(NodePath(from_node));
	GraphNodeExtension* input_node = get_node<GraphNodeExtension>(NodePath(to_node));

	Dictionary input_ports_connected(output_node->get_input_ports_connected_with_output_port());
	if (!input_ports_connected[from_port]) {
		input_ports_connected[from_port] = Dictionary();
	}

	Dictionary input_nodes_connected(input_ports_connected[from_port]);
	if (!input_nodes_connected[to_node]) {
		input_nodes_connected[to_node] = Array();
	}

	Array input_ports_connected_on_input_node(input_nodes_connected[to_node]);
	if (!input_ports_connected_on_input_node.has(to_port)) {
		input_ports_connected_on_input_node.push_back(input_node->get_connection_input_slot(to_port));
	}
	input_ports_connected_on_input_node.sort();
	UtilityFunctions::print(input_ports_connected);

	return OK;
}

void GraphEditExtension::disconnect_node(const StringName& from_node, int from_port, const StringName& to_node,int to_port) {
	GraphEdit::disconnect_node(from_node, from_port, to_node, to_port);

	// TODO 在这里断开连接
	GraphNodeExtension* output_node = get_node<GraphNodeExtension>(NodePath(from_node));
	GraphNodeExtension* input_node = get_node<GraphNodeExtension>(NodePath(to_node));
	Dictionary input_ports_connected(output_node->get_input_ports_connected_with_output_port());
	Dictionary input_nodes_connected(input_ports_connected[from_port]);
	Array input_ports_connected_on_input_node(input_nodes_connected[to_node]);
	int index_input_port = input_node->get_connection_input_slot(to_port);

	input_ports_connected_on_input_node.erase(index_input_port);
	if (input_ports_connected_on_input_node.is_empty()) {
		input_nodes_connected.erase(to_node);
	}
	if (!input_ports_connected[from_port]) {
		input_ports_connected.erase(from_port);
	}

	UtilityFunctions::print("input_ports_connected_on_input_node:  ", input_ports_connected_on_input_node);
	UtilityFunctions::print("input_nodes_connected:  ", input_nodes_connected);
	UtilityFunctions::print("input_ports_connected:  ", input_ports_connected);
}

void GraphNodeExtension::_bind_methods() {
	ClassDB::bind_method(
			D_METHOD(
					"set_slot",
					"slot_index", "enable_left_port", "type_left", "color_left", "enable_right_port", "type_right", "color_right", "custom_icon_left", "custom_icon_right", "draw_stylebox"
			),
			&GraphNodeExtension::set_slot
	);
	ClassDB::bind_method(
			D_METHOD("set_slot_enabled_left", "slot_index", "enable"),
			&GraphNodeExtension::set_slot_enabled_left
	);
	ClassDB::bind_method(
			D_METHOD("set_slot_enabled_right", "slot_index", "enable"),
			&GraphNodeExtension::set_slot_enabled_right
	);

	ClassDB::bind_method(D_METHOD("test_slot"), &GraphNodeExtension::test_slot);
}

GraphNodeExtension::GraphNodeExtension() {

}

GraphNodeExtension::~GraphNodeExtension() {
	int64_t size_input_ports = input_ports.size();
	int64_t size_output_ports = output_ports.size();
	Port* port;

	for (int64_t index_input_port = 0; index_input_port < size_input_ports; ++index_input_port){
		port = get_input_port(index_input_port);
		if (port) {
			memdelete(port);
		}
	}

	for (int64_t index_output_port = 0; index_output_port < size_output_ports; ++index_output_port) {
		port = get_output_port(index_output_port);
		if (port) {
			memdelete(port);
		}
	}
}

void GraphNodeExtension::set_slot(int32_t slot_index,
		bool enable_left_port, int32_t type_left, const Color& color_left,
		bool enable_right_port, int32_t type_right, const Color& color_right,
		const Ref<Texture2D>& custom_icon_left,
		const Ref<Texture2D>& custom_icon_right,
		bool draw_stylebox) {
	GraphNode::set_slot(
			slot_index,
			enable_left_port, type_left, color_left,
			enable_right_port, type_right, color_right,
			custom_icon_left, custom_icon_right, draw_stylebox
	);

	add_input_port(slot_index, enable_left_port);
	add_output_port(slot_index, enable_right_port);
}

void GraphNodeExtension::set_slot_enabled_left(int32_t slot_index, bool enable) {
	GraphNode::set_slot_enabled_left(slot_index, enable);

	add_input_port(slot_index, enable);
}

void GraphNodeExtension::set_slot_enabled_right(int32_t slot_index, bool enable) {
	GraphNode::set_slot_enabled_right(slot_index, enable);

	add_output_port(slot_index, enable);
}

Dictionary GraphNodeExtension::get_input_ports_connected_with_output_port() {
	return input_ports_connected_with_output_port;
}

Port* GraphNodeExtension::get_input_port(int slot_index) const {
	return Object::cast_to<Port>(input_ports[slot_index]);
}

Port* GraphNodeExtension::get_output_port(int slot_index) const {
	return Object::cast_to<Port>(output_ports[slot_index]);
}

void GraphNodeExtension::add_input_port(int slot_index, bool enable) {
	Port* input_port = get_input_port(slot_index);

	if (enable) {
		if (input_port == nullptr) {
			input_ports[slot_index] = memnew(Port);
		}
	} else {
		if (input_port != nullptr) {
			memdelete(input_port);
		}
	}
}

void GraphNodeExtension::add_output_port(int slot_index, bool enable) {
	Port* output_port = get_output_port(slot_index);

	if (enable) {
		if (output_port == nullptr) {
			output_ports[slot_index] = memnew(Port);
		}
	} else {
		if (output_port != nullptr) {
			memdelete(output_port);
		}
	}
}

void GraphNodeExtension::test_slot() {
	UtilityFunctions::print("input_ports_size", input_ports.size());
	UtilityFunctions::print("input_ports:  ", input_ports);
	UtilityFunctions::print("output_ports_size", output_ports.size());
	UtilityFunctions::print("output_ports:  ", output_ports);
}
}//graph_extension