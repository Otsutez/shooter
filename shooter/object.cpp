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

BoundingBox object::Cube::getBoundingBox()
{
	float halfLength = m_size.z / 2.0f;
	float halfWidth = m_size.x / 2.0f;
	float halfHeight = m_size.y / 2.0f;

	return BoundingBox
	{
		Vector3{ m_position.x - halfWidth, m_position.y - halfHeight, m_position.z - halfLength},
		Vector3{ m_position.x + halfWidth, m_position.y + halfHeight, m_position.z + halfLength},

	};
}

void object::Cube::move(Vector3 newPos)
{
	m_position = newPos;
}

void object::Capsule::draw()
{
	DrawCapsule(m_startPos, m_endPos, m_radius, m_slices, m_rings, m_color);
	//DrawCapsuleWires(m_startPos, m_endPos, m_radius, m_slices, m_rings, BLACK);
}

void object::Capsule::move(Vector3 newEndPos)
{
	m_endPos = newEndPos;
	m_startPos = Vector3{ newEndPos.x, newEndPos.y - PLAYER_HEIGHT, newEndPos.z };
}
