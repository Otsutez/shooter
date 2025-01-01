#pragma once
#include "raylib.h"

namespace player
{
	class Player
	{
	public:
		Player();
		void update();
		void draw() {};
		Camera3D m_camera;
	};
}