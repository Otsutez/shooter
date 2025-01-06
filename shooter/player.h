#pragma once
#include "raylib.h"
#include "object.h"
//#include "rcamera.h"

namespace player
{
	class Player
	{
	public:
		Player();
		void update();
		void draw();
		Camera3D getCamera();

	private:
		Camera3D m_camera;
		CameraMode m_camera_mode;
		Vector3 m_position;
		Vector3 m_velocity;
		Vector2 m_lookAngles;
		object::Capsule* m_body;
	};
}