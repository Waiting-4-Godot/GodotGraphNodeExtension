//
// Created by HP on 2023/7/19.
//

#include "godot_node_extension.h"
#include "utils.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/label.hpp>
//#include <utility>


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
	if (p_value != value) {
		value_changed = true;
		value = std::move(p_value);
	}
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
//	UtilityFunctions::print(input_ports_connected);

	output_node->send_value(from_port);

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
	int index_slot = input_node->get_connection_input_slot(to_port);

	input_node->get_input_port(index_slot)->set_value(nullptr);
	input_ports_connected_on_input_node.erase(index_slot);
	if (input_ports_connected_on_input_node.is_empty()) {
		input_nodes_connected.erase(to_node);
	}
	if (!input_ports_connected[from_port]) {
		input_ports_connected.erase(from_port);
	}

//	UtilityFunctions::print("input_ports_connected_on_input_node:  ", input_ports_connected_on_input_node);
//	UtilityFunctions::print("input_nodes_connected:  ", input_nodes_connected);
//	UtilityFunctions::print("input_ports_connected:  ", input_ports_connected);
}

void GraphNodeExtension::_bind_methods() {
	// overwrite
	ClassDB::bind_method(
			D_METHOD(
					"set_slot",
					"slot_index", "enable_left_port", "type_left", "color_left", "enable_right_port", "type_right", "color_right", "custom_icon_left", "custom_icon_right", "draw_stylebox"
			),
			&GraphNodeExtension::set_slot,
			DEFVAL(true), DEFVAL(Variant::INT), DEFVAL(Color(1, 1, 1, 1)),
			DEFVAL(true), DEFVAL(Variant::INT), DEFVAL(Color(1, 1, 1, 1)),
			DEFVAL(nullptr), DEFVAL(nullptr), DEFVAL(true)
	);
	ClassDB::bind_method(
			D_METHOD("set_slot_enabled_left", "slot_index", "enable"),
			&GraphNodeExtension::set_slot_enabled_left
	);
	ClassDB::bind_method(
			D_METHOD("set_slot_enabled_right", "slot_index", "enable"),
			&GraphNodeExtension::set_slot_enabled_right
	);

	// setter & getter
	ClassDB::bind_method(D_METHOD("set_mode", "mode"), &GraphNodeExtension::set_mode);
	ClassDB::bind_method(D_METHOD("get_mode"), &GraphNodeExtension::get_mode);

	// other

	// test
	ClassDB::bind_method(D_METHOD("test_slot"), &GraphNodeExtension::test_slot);

	// property
	ClassDB::add_property(
			"GraphNodeExtension",
			PropertyInfo(Variant::INT, "mode",
						 PROPERTY_HINT_ENUM, "Data Source, Data Processing, Data Display"),
			"set_mode",
			"get_mode"
	);

	// constant

}

void GraphNodeExtension::_notification(int p_what) {
	switch ( p_what ) {
	case NOTIFICATION_READY:
		UtilityFunctions::print(get_name(), "ready");
		break;
	case NOTIFICATION_PROCESS:
		what_to_do();
		when_value_changed();
		break;
	case NOTIFICATION_DRAG_BEGIN:
		UtilityFunctions::print("drag begin");
	default:
		break;
	}
}


GraphNodeExtension::GraphNodeExtension() {
	mode = DATA_SOURCE;
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

void GraphNodeExtension::_process(double delta) {

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

// setter & getter
Dictionary GraphNodeExtension::get_input_ports_connected_with_output_port() {
	return input_ports_connected_with_output_port;
}

void GraphNodeExtension::set_mode(Mode p_mode) {
	mode = p_mode;
}

GraphNodeExtension::Mode GraphNodeExtension::get_mode() const {
	return mode;
}

// other
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

void GraphNodeExtension::data_source() {
//	UtilityFunctions::print(get_name());
	int count_output_port = get_connection_output_count();

	for (int index_output_port = 0; index_output_port < count_output_port; ++index_output_port) {
//		UtilityFunctions::print(index_output_port);
		int index_slot = get_connection_output_slot(index_output_port);
//		UtilityFunctions::print(index_slot);

		Node* child_node = get_child(index_slot);
		Variant node_property = utils::ControlUtils::get_node_property(child_node);
//		UtilityFunctions::print(node_property);
		Variant::Type type_output_port = (Variant::Type)get_connection_output_type(index_output_port);
//		UtilityFunctions::print(type_output_port);

		switch ( type_output_port ) {
		case Variant::BOOL:
			set_data_source<bool>(get_output_port(index_slot), node_property);
			break;
		case Variant::INT:
			set_data_source<int>(get_output_port(index_slot), node_property);
			break;
		case Variant::FLOAT:
			set_data_source<float>(get_output_port(index_slot), node_property);
			break;
		case Variant::STRING:
			set_data_source<String>(get_output_port(index_slot), node_property);
			break;
		default:
			break;
		}

//		UtilityFunctions::print(get_output_port(index_slot)->get_value());
	}
}

void GraphNodeExtension::send_value(int index_output_port) {
	// 与该输出端口连接的哪些节点的哪些输入端口
	Dictionary input_nodes_and_ports = input_ports_connected_with_output_port[index_output_port];
	// 与该输出端口连接的所有节点
	Array input_nodes_connected = input_nodes_and_ports.keys();
	int64_t count_input_nodes = input_nodes_connected.size();

//	UtilityFunctions::print(input_nodes_and_ports);
//	UtilityFunctions::print(input_nodes_connected);
//	UtilityFunctions::print(count_input_nodes);

	for (int index_input_node = 0; index_input_node < count_input_nodes; ++index_input_node) {
		StringName node_name = input_nodes_connected[index_input_node];
		auto* node = get_parent()->get_node<GraphNodeExtension>(NodePath(node_name));
		Array input_ports_on_this_node = input_nodes_and_ports.get(node_name, nullptr);
		int64_t count_input_ports = input_ports_on_this_node.size();
		Variant value = get_output_port(get_connection_output_slot(index_output_port))->get_value();

//		UtilityFunctions::print(get_connection_output_slot(index_output_port));
//		UtilityFunctions::print("name:  ", node->get_name());
//		UtilityFunctions::print("input ports:  ", input_ports_on_this_node);
//		UtilityFunctions::print("count:  ", count_input_ports);
//		UtilityFunctions::print("value:  ", value);

		for (int index_input_port = 0; index_input_port < count_input_ports; ++index_input_port) {
			int slot_index = input_ports_on_this_node[index_input_port];
			UtilityFunctions::print(node->get_name(), "  slot_index:  ", slot_index);
			node->get_input_port((slot_index))->set_value(value);
			UtilityFunctions::print(node->get_input_port(slot_index)->get_value());
		}
	}
}

void GraphNodeExtension::data_display() {
	int64_t count_slot_with_input_port = input_ports.size();
//	UtilityFunctions::print(get_name(), count_slot_with_input_port);

	for (int index_input_slot = 0; index_input_slot < count_slot_with_input_port; ++index_input_slot) {
		if (input_ports[index_input_slot]) {
//			UtilityFunctions::print(index_input_slot);
			Variant value = get_input_port(index_input_slot)->get_value();
			Label* label = Object::cast_to<Label>(get_child(index_input_slot));
			label->set_text(value);
		}
	}
}

void GraphNodeExtension::what_to_do() {
	switch ( mode ) {
	case DATA_SOURCE:
		data_source();
		break;
	case DATA_PROCESSING:
		// TODO
		break;
	case DATA_DISPLAY:
		data_display();
		break;
	}
}

void GraphNodeExtension::when_value_changed() {
	int64_t count_output_port = get_connection_output_count();

	for ( int index_output_port = 0; index_output_port < count_output_port; index_output_port++) {
		int index_slot = get_connection_output_slot(index_output_port);
		Port* output_port = get_output_port(index_slot);

		if (output_port->is_value_changed()) {
			send_value(index_output_port);
			output_port->set_value_changed(false);
		}
	}
}

// test
void GraphNodeExtension::test_slot() {
//	UtilityFunctions::print("input_ports_size", input_ports.size());
//	UtilityFunctions::print("input_ports:  ", input_ports);
//	UtilityFunctions::print("output_ports_size", output_ports.size());
//	UtilityFunctions::print("output_ports:  ", output_ports);
//	send_value(0);
//	UtilityFunctions::print(input_ports);
	when_value_changed();
}


}//graph_extension