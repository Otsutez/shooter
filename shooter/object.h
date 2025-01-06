#pragma once
#include "raylib.h"

namespace object
{
	// Object interface
	class Object
	{
	public:
		virtual ~Object() {}
		virtual void draw() {}
	};

	// Plane
	class Plane : public Object
	{
	public:
		Plane(Vector3 centerPos, Vector2 size, Color color) :
			m_centerPos{ centerPos },
			m_size{ size },
			m_color{ color } {
		}

		virtual void draw();

	private:
		Vector3 m_centerPos;
		Vector2 m_size;
		Color m_color;
	};

	// Cube
	class Cube : public Object
	{
	public:
		Cube(Vector3 position, Vector3 size, Color color) :
			m_position{ position },
			m_size{ size },
			m_color{ color } {
		}

		virtual void draw();
		void move(Vector3 newPos);
	private:
		Vector3 m_position;
		Vector3 m_size;
		Color m_color;
	};

	// Capsule
	class Capsule
	{
	public:
		Capsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) :
			m_startPos{ startPos },
			m_endPos{ endPos },
			m_radius{ radius },
			m_slices{ slices },
			m_rings{ rings },
			m_color{ color } {
		}

		virtual void draw();
		void move(Vector3 newStartPos);

	private:
		Vector3 m_startPos;
		Vector3 m_endPos;
		float m_radius;
		int m_slices;
		int m_rings;
		Color m_color;
	};
}