#pragma once
#include "raylib.h"
#include "object.h"
#include "raymath.h"
#include "config.h"
#include <vector>

namespace player
{
	class Player
	{
	public:
		Player();
		void update(std::vector<object::Cube*>& objects);
		Vector3 displacementAfterCollision(Vector3 newPos, std::vector<object::Cube*>& objects);
		BoundingBox getBoundingBox(Vector3 pos);
		void draw();
		Camera3D getCamera();

	private:
		Camera3D m_camera;
		object::Capsule* m_body;
		Vector3 m_velocity;
		bool m_jumping;
	};
}