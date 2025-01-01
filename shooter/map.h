#pragma once
#include <vector>
#include "raylib.h"

namespace map
{
	// Object interface
	class Object
	{
	public:
		virtual ~Object() {}
		virtual void draw() {}
	};


	class Plane : public Object
	{
	public:
		Plane(Vector3 centerPos, Vector2 size, Color color) :
			m_centerPos{ centerPos },
			m_size{ size },
			m_color{ color } {}

		virtual void draw();

	private:
		Vector3 m_centerPos;
		Vector2 m_size;
		Color m_color;
	};

	class Cube : public Object
	{
	public:
		Cube(Vector3 position, Vector3 size, Color color) :
			m_position {position },
			m_size{ size },
			m_color{ color } {}

		virtual void draw();
	private:
		Vector3 m_position;
		Vector3 m_size;
		Color m_color;
	};

	class Map
	{
	public:
		Map();
		void draw();

	private:
		std::vector<Object*> m_objects;
	};
}