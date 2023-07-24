extends GraphEditExtension

@onready var input: GraphNodeExtension = $Input
@onready var enable: GraphNodeExtension = $Enable
@onready var display: GraphNodeExtension = $Display
@onready var check_button: CheckButton = $Input/CheckButton
@onready var check_button2: CheckButton = $Input/CheckButton2
@onready var check_button3: CheckButton = $Input/CheckButton3
@onready var timer: Timer = $"../Timer"

var count: int = 0

# Called when the node enters the scene tree for the first time.
func _ready():
	init_slot(input, 3, false, true)
	init_slot(enable, 2, false, true)
	init_slot(display, 8, true, false)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func init_slot(node: GraphNodeExtension, num: int, enable_input_port: bool, enable_output_port: bool) -> void:
	for i in num:
		node.set_slot(i, enable_input_port, TYPE_BOOL, Color.CHARTREUSE, enable_output_port, TYPE_BOOL, Color.TOMATO)

func set_input(input3: int, input2: int, input: int) -> void:
	check_button.button_pressed = input
	check_button2.button_pressed = input2
	check_button3.button_pressed = input3


func _on_connection_request(from_node, from_port, to_node, to_port):
	connect_node(from_node, from_port, to_node, to_port)


func _on_disconnection_request(from_node, from_port, to_node, to_port):
	disconnect_node(from_node, from_port, to_node, to_port)


func _on_timer_timeout():
	if count % 8 == 0:
		set_input(false, false, false)
	elif  count % 8== 1:
		set_input(false, false, true)
	elif count % 8 == 2:
		set_input(false, true, false)
	elif count % 8 == 3:
		set_input(false, true, true)
	elif count % 8 == 4:
		set_input(true, false, false)
	elif count % 8 == 5:
		set_input(true, false, true)
	elif count % 8 == 6:
		set_input(true, true, false)
	elif count % 8 == 7:
		set_input(true, true, true)
	
	count += 1


func _on_button_pressed():
	timer.start(1)
