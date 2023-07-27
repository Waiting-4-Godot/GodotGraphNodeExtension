extends GraphNodeExtension

@onready var label: Label = $Label
@onready var label2: Label = $Label2


# Called when the node enters the scene tree for the first time.
func _ready():
	set_slot(0, true, TYPE_INT, Color.ORANGE, true, TYPE_INT, Color.YELLOW_GREEN)
	set_slot(1, true, TYPE_INT, Color.ORANGE, false)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	divide()


func divide() -> void:
	var a = get_value_input_port(0)
	var b = get_value_input_port(1)
	if a != null:
		label.text = str(a)
	else:
		return 
	if b != null:
		label2.text = str(b)
	else:
		return 
	if b != 0:
		set_value_output_port(0, a / b)
	else:
		set_value_output_port(0, null)
