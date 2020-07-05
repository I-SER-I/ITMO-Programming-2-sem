#pragma once
#include "Constants.h"
#include "Cube.h"

namespace RubiksCube
{
	struct Animation
	{
		int frame_count;
		static const int MAX_FRAME = 90;
        static const int STEP = 6;
        static const int FPS = 90;
		ROTATE_METHOD rotate_method = N;
		Animation(ROTATE_METHOD rotate_method) : frame_count(0), rotate_method(rotate_method){}
	};
	void initDisplay(const RubiksCube::Cube &cb);
	void startDisplay();
	void loadOperation(const ROTATE_METHOD *s);
}
