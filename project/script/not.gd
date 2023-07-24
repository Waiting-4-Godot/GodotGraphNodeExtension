extends GraphNodeExtension


# Called when the node enters the scene tree for the first time.
func _ready():
	set_slot(0, true, TYPE_BOOL, Color.AQUA, true, TYPE_BOOL, Color.VIOLET)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	NOT()

func NOT() -> void:
	set_value_output_port(0, not get_value_input_port(0))