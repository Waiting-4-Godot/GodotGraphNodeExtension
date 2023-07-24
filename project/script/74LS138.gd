extends GraphNodeExtension

# Called when the node enters the scene tree for the first time.
func _ready():
	init_slot()
	init_three_eight_decoder()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	three_eight_decoder()

func init_slot() -> void:
	set_slot(0, true, TYPE_BOOL, Color.BLUE_VIOLET, true, TYPE_BOOL, Color.AQUA)
	set_slot(1, true, TYPE_BOOL, Color.BLUE_VIOLET, true, TYPE_BOOL, Color.AQUA)
	set_slot(2, true, TYPE_BOOL, Color.BLUE_VIOLET, true, TYPE_BOOL, Color.AQUA)
	set_slot(3, false, TYPE_BOOL, Color.BLUE_VIOLET, true, TYPE_BOOL, Color.AQUA)
	set_slot(4, false, TYPE_BOOL, Color.BLUE_VIOLET, true, TYPE_BOOL, Color.AQUA)
	set_slot(5, true, TYPE_BOOL, Color.BLUE_VIOLET, true, TYPE_BOOL, Color.AQUA)
	set_slot(6, true, TYPE_BOOL, Color.AQUA, true, TYPE_BOOL, Color.AQUA)
	set_slot(7, true, TYPE_BOOL, Color.AQUA, true, TYPE_BOOL, Color.AQUA)


func init_three_eight_decoder() -> void:
	var num = get_connection_output_count()
	for i in num:
		set_value_output_port(i, true)


func three_eight_decoder() -> void:
	var input = get_value_input_port(0)
	var input2 = get_value_input_port(1)
	var input3 = get_value_input_port(2)
	var enable = get_value_input_port(3)
	var enable2 = get_value_input_port(4)
	var enable3 = get_value_input_port(5)
	
	if enable:
		if (not input3 and not input2 and not input):  # 000 -> 0
			init_three_eight_decoder()
			set_value_output_port(0, false)
		elif (not input3 and not input2 and input):  # 001 -> 1
			init_three_eight_decoder()
			set_value_output_port(1, false)
		elif (not input3 and input2 and not input):  # 010 -> 2
			init_three_eight_decoder()
			set_value_output_port(2, false)
		elif (not input3 and input2 and input):  # 011 -> 3
			init_three_eight_decoder()
			set_value_output_port(3, false)
		elif (input3 and not input2 and not input):  # 100 -> 4
			init_three_eight_decoder()
			set_value_output_port(4, false)
		elif (input3 and not input2 and input):  # 101 -> 5
			init_three_eight_decoder()
			set_value_output_port(5, false)
		elif (input3 and input2 and not input):  #  110 -> 6
			init_three_eight_decoder()
			set_value_output_port(6, false)
		elif (input3 and input2 and input):  # 111 -> 7
			init_three_eight_decoder()
			set_value_output_port(7, false)
