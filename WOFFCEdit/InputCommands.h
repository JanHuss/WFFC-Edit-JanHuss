#pragma once
#include <vector>

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool up;
	bool down;
	bool rotRight;
	bool rotLeft;
	bool rotUP;
	bool rotDown;

	int mouse_x;
	int mouse_y;
	bool mouse_lb_Down;
};
