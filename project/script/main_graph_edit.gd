extends GraphEditExtension

@onready var test: GraphNodeExtension = $Test
@onready var graph_node: GraphNodeExtension = $GraphNode
@onready var graph_node2: GraphNodeExtension = $GraphNode2

# Called when the node enters the scene tree for the first time.
func _ready():
	init_slot()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func init_slot() -> void:
	test.set_slot(0, true, TYPE_INT, Color.ANTIQUE_WHITE, true, TYPE_INT, Color.AQUA, null, null, true)
	test.set_slot(1, true, TYPE_INT, Color.ANTIQUE_WHITE, true, TYPE_INT, Color.AQUA, null, null, true)
	graph_node.set_slot(0, true, TYPE_INT, Color.BURLYWOOD, true, TYPE_INT, Color.YELLOW_GREEN, null, null, true)
	graph_node.set_slot(1, true, TYPE_INT, Color.BURLYWOOD, true, TYPE_INT, Color.YELLOW_GREEN, null, null, true)
	graph_node2.set_slot(0, true, TYPE_INT, Color.YELLOW, true, TYPE_INT, Color.CORAL, null, null, true)
	graph_node2.set_slot(1, true, TYPE_INT, Color.YELLOW, true, TYPE_INT, Color.CORAL, null, null, true)
	


func _on_button_pressed():
	test.test_slot()
	test.free()


func _on_connection_request(from_node, from_port, to_node, to_port):
	connect_node(from_node, from_port, to_node, to_port)


func _on_disconnection_request(from_node, from_port, to_node, to_port):
	disconnect_node(from_node, from_port, to_node, to_port)
