extends GraphEditExtension

@onready var test: GraphNodeExtension = $Test

# Called when the node enters the scene tree for the first time.
func _ready():
	test.set_slot(0, true, TYPE_INT, Color.ANTIQUE_WHITE, true, TYPE_INT, Color.AQUA, null, null, true);
	test.set_slot(1, true, TYPE_INT, Color.ANTIQUE_WHITE, true, TYPE_INT, Color.AQUA, null, null, true);
	
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_button_pressed():
	test.test_slot()
	test.free()
