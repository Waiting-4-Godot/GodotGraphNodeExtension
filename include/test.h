//
// Created by HP on 2023/7/19.
//

#ifndef GRAPHEXTENSION_TEST_H
#define GRAPHEXTENSION_TEST_H

#include <godot_cpp/classes/sprite2d.hpp>

using namespace godot;

class Test: public Sprite2D{
	GDCLASS(Test, Sprite2D)
protected:
	static void _bind_methods();

public:
	void _process(double delta);
};

#endif //GRAPHEXTENSION_TEST_H
