#pragma once
#include <vector>
#include "raylib.h"
#include "object.h"
#include "config.h"

namespace map
{
	class Map
	{
	public:
		Map();
		void draw(Camera3D camera);
		std::vector<object::Cube*>& getObjects();

	private:
		object::Plane* m_plane;
		std::vector<object::Cube*> m_objects;
		int m_map[MAP_LENGTH][MAP_WIDTH];
	};
}