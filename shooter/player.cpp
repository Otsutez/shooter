#include "player.h"

using namespace player;

Player::Player()
{
    Camera3D camera{ 0 };
    camera.position = Vector3{ 10.0f, 2.0f, 0.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    m_camera = camera;
}
void Player::update()
{
    UpdateCamera(&m_camera, CAMERA_FIRST_PERSON);
}
;

