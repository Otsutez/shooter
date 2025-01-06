#include "map.h"
#include "config.h"
#include "object.h"

map::Map::Map() :
	m_map {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
}
{
   
	float center = MAP_WIDTH / 2.0f;

    // Construct map
	// construct plane
	float mapLength = MAP_LENGTH * TILE_SIZE;
	float mapWidth = MAP_WIDTH * TILE_SIZE;
	m_objects.push_back(new object::Plane{ ORIGIN, Vector2 {mapLength, mapWidth}, GRAY });

	// Construct walls
	float wallOffset = mapLength / 2 + TILE_SIZE / 2.0f;
	m_objects.push_back(new object::Cube{ Vector3 {wallOffset, TILE_SIZE, 0.0f}, Vector3 {TILE_SIZE, TILE_SIZE * 2.0f, mapLength}, DARKGRAY});
	m_objects.push_back(new object::Cube{ Vector3 {-wallOffset, TILE_SIZE, 0.0f}, Vector3 {TILE_SIZE, TILE_SIZE * 2.0f, mapLength}, DARKGRAY});
	m_objects.push_back(new object::Cube{ Vector3 {0.0f, TILE_SIZE, wallOffset}, Vector3 {mapLength, TILE_SIZE * 2.0f, TILE_SIZE}, DARKGRAY});
	m_objects.push_back(new object::Cube{ Vector3 {0.0f, TILE_SIZE, -wallOffset}, Vector3 {mapLength, TILE_SIZE * 2.0f, TILE_SIZE}, DARKGRAY});

	// Construct cubes
	for (int i = 0; i < MAP_LENGTH; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			int cubeHeight = m_map[i][j];
			if (cubeHeight != 0)
			{
				Vector3 cubeSize = { TILE_SIZE, TILE_SIZE * cubeHeight, TILE_SIZE };
				Vector3 cubePosition = { (i - center) * TILE_SIZE, cubeHeight / 2.0f * TILE_SIZE, (j - center) * TILE_SIZE };
				m_objects.push_back(new object::Cube{ cubePosition, cubeSize, RED });
			}
		}
	}
}

void map::Map::draw()
{
	for (object::Object* object : m_objects) {
		object->draw();
	}
}
