#include "object.h"
#include "config.h"

void object::Plane::draw()
{
	DrawPlane(m_centerPos, m_size, m_color);
}

void object::Cube::draw()
{
	DrawCubeV(m_position, m_size, m_color);
	DrawCubeWiresV(m_position, m_size, BLACK);
}

void object::Cube::move(Vector3 newPos)
{
	m_position = newPos;
}

void object::Capsule::draw()
{
	DrawCapsule(m_startPos, m_endPos, m_radius, m_slices, m_rings, m_color);
	//DrawCapsuleWires(m_startPos, m_endPos, m_radius, m_slices, m_rings, m_color);
}

void object::Capsule::move(Vector3 newEndPos)
{
	m_endPos = newEndPos;
	m_startPos = Vector3{ newEndPos.x, newEndPos.y - PLAYER_HEIGHT, newEndPos.z };
}
