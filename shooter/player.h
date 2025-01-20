#pragma once
#include "raylib.h"
#include "object.h"
#include "raymath.h"
#include "config.h"
#include <vector>

namespace player
{

	enum PistolState
	{
		idle = 0,
		shoot1,
		shoot2,
		shoot3,
		shoot4
	};

	class Pistol
	{
	public:
		Pistol();
		void update();
		void draw();

	private:
		PistolState m_state;
		float m_cooldown;
		Texture2D m_gun;
		Rectangle m_frameRec;
	};

	class Player
	{
	public:
		Player(Vector3 pos);
		void update(std::vector<object::Cube*>& objects);
		Vector3 displacementAfterCollision(Vector3 newPos, std::vector<object::Cube*>& objects);
		BoundingBox getBoundingBox(Vector3 pos);
		void draw();
		void draw(Camera3D camera);
		Camera3D getCamera();

	private:
		Camera3D m_camera;
		object::Capsule* m_body;
		Vector3 m_velocity;
		bool m_jumping;
		Pistol* m_pistol;
	};
}