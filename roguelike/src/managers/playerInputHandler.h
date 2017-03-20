#pragma once
#include "../math/vec2.h"

enum INPUT_TYPES {Moving, OpenInventory, Exit};

class PlayerInputHandler 
{
private: 
	INPUT_TYPES _inputType;
	vec2 _movingDirection;
public:
	void input();
	INPUT_TYPES getInputType() { return _inputType; }
	vec2 getMovingDirection() { return _movingDirection; }
};