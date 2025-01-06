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
		void draw();

	private:
		std::vector<object::Object*> m_objects;
		int m_map[MAP_LENGTH][MAP_WIDTH];
	};
}