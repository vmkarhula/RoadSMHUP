#pragma once

#include <vector>

struct InputEvent;

using EventQueue = std::vector<InputEvent>;

struct InputEvent
{
	enum class InputCode
	{
		Up,
		Down,
		Left,
		Right,
		ZoomOut,
		ZoomIn,
		Fire1,
		Fire2
	};

	InputCode code;

};
