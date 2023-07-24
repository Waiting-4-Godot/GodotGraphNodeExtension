extends GraphNodeExtension

@onready var label: Label = $Label
@onready var label2: Label = $Label2


# Called when the node enters the scene tree for the first time.
func _ready():
	print("ready?")
	set_slot(0);
	set_slot(1, true, TYPE_INT, Color.ANTIQUE_WHITE, false, TYPE_INT, Color.AQUA);
	print("readied!")
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	add()

func add() -> void:
	var a = get_value_input_port(0)
	var b = get_value_input_port(1)
	if a != null:
		label.text = str(a)
	if b != null:
		label2.text = str(b)
	if a != null and b != null:
		set_value_output_port(0, a + b)
