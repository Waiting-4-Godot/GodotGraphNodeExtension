extends GraphNodeExtension


# Called when the node enters the scene tree for the first time.
func _ready():
	set_slot(0, true, TYPE_BOOL, Color.AQUA, true, TYPE_BOOL, Color.VIOLET)
	set_slot(1, true, TYPE_BOOL, Color.AQUA, false, TYPE_BOOL, Color.VIOLET)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	OR()


func OR() -> void:
	set_value_output_port(0, get_value_input_port(0) or get_value_input_port(1))
