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

private:
	Variant value;
};


class GraphEditExtension : public GraphEdit {
	GDCLASS(GraphEditExtension, GraphEdit)
protected:
	static void _bind_methods();
};


class GraphNodeExtension : public GraphNode {
	GDCLASS(GraphNodeExtension, GraphNode)
protected:
	static void _bind_methods();
};

}// graph_extension

#endif //GRAPHEXTENSION_GODOT_NODE_EXTENSION_H
