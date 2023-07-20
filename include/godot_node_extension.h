//
// Created by HP on 2023/7/19.
//

#ifndef GRAPHEXTENSION_GODOT_NODE_EXTENSION_H
#define GRAPHEXTENSION_GODOT_NODE_EXTENSION_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/graph_edit.hpp>
#include <godot_cpp/classes/graph_node.hpp>


using namespace godot;

namespace graph_extension {

class Port : public Object {
	GDCLASS(Port, Object)
protected:
	static void _bind_methods();

public:
	Port();
	~Port();

	// setter & getter
	void set_value(Variant p_value);
	Variant get_value() const;
	void set_value_changed(bool p_value_changed);
	bool is_value_changed() const;

private:
	Variant value;
	bool value_changed;
};


class GraphEditExtension : public GraphEdit {
	GDCLASS(GraphEditExtension, GraphEdit)
protected:
	static void _bind_methods();

public:
	Error connect_node(const StringName& from_node, int from_port, const StringName& to_node, int to_port);
	void disconnect_node(const StringName& from_node, int from_port, const StringName& to_node, int to_port);
};


class GraphNodeExtension : public GraphNode {
	GDCLASS(GraphNodeExtension, GraphNode)
protected:
	static void _bind_methods();


public:
	GraphNodeExtension();
	~GraphNodeExtension();

	// overwrite
	void set_slot(int32_t slot_index,
			bool enable_left_port, int32_t type_left, const Color &color_left,
			bool enable_right_port,int32_t type_right, const Color &color_right,
			const Ref<Texture2D> &custom_icon_left = nullptr,
			const Ref<Texture2D> &custom_icon_right = nullptr,
			bool draw_stylebox = true);
	void set_slot_enabled_left(int32_t slot_index, bool enable);
	void set_slot_enabled_right(int32_t slot_index, bool enable);

	// setter & getter
	Dictionary get_input_ports_connected_with_output_port();

	// other
	Port* get_input_port(int slot_index) const;
	Port* get_output_port(int slot_index) const;
	void add_input_port(int slot_index, bool enable);
	void add_output_port(int slot_index, bool enable);

	//test
	void test_slot();

private:
	Dictionary input_ports;
	Dictionary output_ports;
	Dictionary input_ports_connected_with_output_port;
};

}// graph_extension

#endif //GRAPHEXTENSION_GODOT_NODE_EXTENSION_H