extends GraphEditExtension

@onready var test: GraphNodeExtension = $Test
@onready var graph_node: GraphNodeExtension = $GraphNode
@onready var graph_node2: GraphNodeExtension = $GraphNode2

# Called when the node enters the scene tree for the first time.
func _ready():
	init_slot()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
#	add.is_processing()
	pass


func init_slot() -> void:
	test.set_slot(0, true, TYPE_INT, Color.ANTIQUE_WHITE, true, TYPE_INT, Color.AQUA)
	test.set_slot(1, false, TYPE_INT, Color.ANTIQUE_WHITE, true, TYPE_INT, Color.AQUA)
	test.set_slot(3)
	test.set_slot(4)
	graph_node.set_slot(0, false, TYPE_INT, Color.BURLYWOOD, false, TYPE_INT, Color.YELLOW_GREEN)
	graph_node.set_slot(1, true, TYPE_INT, Color.BURLYWOOD, true, TYPE_INT, Color.YELLOW_GREEN)
	graph_node2.set_slot(0, true, TYPE_INT, Color.YELLOW, true, TYPE_INT, Color.CORAL)
	graph_node2.set_slot(1, true, TYPE_INT, Color.YELLOW, true, TYPE_INT, Color.CORAL)


func _on_button_pressed():
#	add.test_slot()
	graph_node.test_slot()
#	test.test_slot()
#	graph_node.test_slot()
#	graph_node2.test_slot()
#	pass


func _on_connection_request(from_node, from_port, to_node, to_port):
	connect_node(from_node, from_port, to_node, to_port)


func _on_disconnection_request(from_node, from_port, to_node, to_port):
	disconnect_node(from_node, from_port, to_node, to_port)
