#include "player.h"
#include "config.h"
#include "object.h"
#include "raymath.h"

using namespace player;

Player::Player()
{
    // Initialize player physics
    m_position = Vector3{ PLAYER_START_X * TILE_SIZE, PLAYER_START_Y, PLAYER_START_Z};
    m_velocity = Vector3{};
    m_lookAngles = Vector2{};

    // Initialize camera
    Camera3D camera{ 0 };
    camera.position = Vector3{ m_position.x, PLAYER_HEIGHT, m_position.z };
    camera.target = Vector3{ -1.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    m_camera = camera;
    m_camera_mode = CAMERA_FIRST_PERSON;

    // Initialize player capsule body
    Vector3 startPos = Vector3{ m_position.x, m_position.y, m_position.z };
    Vector3 endPos = Vector3{ m_position.x, PLAYER_HEIGHT, m_position.z };
    m_body = new object::Capsule{ startPos, endPos, CAPSULE_RADIUS, CAPSULE_SLICES, CAPSULE_RINGS, YELLOW };
}

void Player::update()
{
    // ----------------------------------------------------------------
    // Change player direction due to mouse input
    // Logic taken from https://github.com/raysan5/raylib/blob/master/src/rcamera.h
    // ----------------------------------------------------------------
    Vector2 mouseDelta = GetMouseDelta();
    Vector3 up = m_camera.up;
    Vector3 forward = Vector3Subtract(m_camera.target, m_camera.position);
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, up));
    float yawAngle = -mouseDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY;
    float pitchAngle = -mouseDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY;

    // Rotate forward vector around up axis to rotate camera left/right
    forward = Vector3RotateByAxisAngle(forward, m_camera.up, yawAngle);
    
    // Clamp view up
    float maxAngleUp = Vector3Angle(up, forward);
    maxAngleUp -= 0.001f; // avoid numerical errors
    if (pitchAngle > maxAngleUp) pitchAngle = maxAngleUp;

    // Clamp view down
    float maxAngleDown = Vector3Angle(Vector3Negate(up), forward);
    maxAngleDown *= -1.0f; // downwards angle is negative
    maxAngleDown += 0.001f; // avoid numerical errors
    if (pitchAngle < maxAngleDown) pitchAngle = maxAngleDown;

    // Rotate forward vector around right axis to rotate camera up/down
    forward = Vector3RotateByAxisAngle(forward, right, pitchAngle);

    // Move target relative to position
    m_camera.target = m_camera.position + forward;

    // ----------------------------------------------------------------
    // Change player position due to keyboard input
    // Inspiration from https://gist.github.com/sumofat/1645897853232b1e46b941c4e5197ed5
    // ----------------------------------------------------------------

    float dt = GetFrameTime();

    // Remove y component from our calculated forward to 
    // restrict movement to the ground
    forward.y = 0;
    forward = Vector3Normalize(forward);

    // Change velocity with respect to input
    if (IsKeyDown('W'))
    {
        m_velocity += forward * dt * SPEED;
    }
    if (IsKeyDown('S'))
    {
        m_velocity -= forward * dt * SPEED;
    }
    if (IsKeyDown('D'))
    {
        m_velocity += right * dt * SPEED;
    }
    if (IsKeyDown('A'))
    {
        m_velocity -= right * dt * SPEED;
    }

    // Damping
    m_velocity *= 0.85625f;

    // Change camera position with respect to velocity
    Vector3 displacement = m_velocity * dt;
    m_camera.position += displacement;
    m_camera.target += displacement;

    // Move body to camera position
    m_body->move(m_camera.position);

}
void player::Player::draw()
{
    m_body->draw();
}
Camera3D Player::getCamera()
{
    return m_camera;
}



