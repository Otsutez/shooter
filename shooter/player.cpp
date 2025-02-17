#include "player.h"

using namespace player;

Player::Player(Vector3 pos)
{
    // Initialize camera
    Camera3D camera{ 0 };
    camera.position = Vector3{ pos.x * TILE_SIZE, PLAYER_HEIGHT, pos.z * TILE_SIZE };
    camera.target = Vector3{ -1.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    m_camera = camera;

    // Initialize player capsule body
    Vector3 startPos = Vector3{ m_camera.position.x, 0.0f, m_camera.position.z };
    Vector3 endPos = Vector3{ m_camera.position.x, PLAYER_HEIGHT, m_camera.position.z };
    m_body = new object::Capsule{ startPos, endPos, CAPSULE_RADIUS, CAPSULE_SLICES, CAPSULE_RINGS, GREEN };

    // Initialize player state
    m_velocity = Vector3{ 0.0f, 0.0f, 0.0f };
    m_jumping = false;
    m_pistol = new Pistol;
}

void Player::update(std::vector<object::Cube*>& objects)
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
    // Inspiration from https://gist.github.com/jakubtomsu/9cae5298f86d2b9d2aed48641a1a3dbd
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

    //// Gravity
    //if (m_camera.position.y - PLAYER_HEIGHT > 0)
    //{
    //    m_velocity.y -= dt * 15 + 0.3;
    //}
    //else
    //{
    //    m_jumping = false;
    //}

    //// Jumping
    //if (IsKeyDown(' '))
    //{
    //    if (!m_jumping) {
    //        m_velocity.y = 15;
    //        m_jumping = true;
    //    }
    //}

    // Damping
    m_velocity *= 0.85625f;

    // Check collision
    Vector3 displacement = m_velocity * dt;
    Vector3 newDisplacement = displacementAfterCollision(displacement, objects);

    // Change camera position with respect to new displacement
    m_camera.position += newDisplacement;
    m_camera.target += newDisplacement;
    
    // Move body to camera position
    m_body->move(m_camera.position);

    // Gun
    m_pistol->update();
}
Vector3 player::Player::displacementAfterCollision(Vector3 displacement, std::vector<object::Cube*>& objects)
{

    TraceLog(LOG_DEBUG, "Collision detected");
    // Check horizontal collision
    Vector3 newXPos = Vector3{ m_camera.position.x + displacement.x, m_camera.position.y, m_camera.position.z };
    for (object::Cube* cube : objects)
    {
        if (CheckCollisionBoxes(getBoundingBox(newXPos), cube->getBoundingBox()) == true) {
            displacement.x = 0;
            
            break;
        }
    }

    // Check vertical
    Vector3 newYPos = Vector3{ m_camera.position.x, m_camera.position.y, m_camera.position.z + displacement.z };
    for (object::Cube* cube : objects)
    {
        if (CheckCollisionBoxes(getBoundingBox(newYPos), cube->getBoundingBox()) == true) {
            displacement.z = 0;
            break;
        }
    }

    return displacement;

}

BoundingBox player::Player::getBoundingBox(Vector3 pos)
{
    return BoundingBox
    {
        Vector3 {pos.x - CAPSULE_RADIUS, pos.y - 2.0f, pos.z - CAPSULE_RADIUS},
        Vector3 {pos.x + CAPSULE_RADIUS, pos.y, pos.z + CAPSULE_RADIUS}
    };
}

void player::Player::draw()
{
    BeginMode3D(m_camera);
    m_body->draw();
    EndMode3D();
    m_pistol->draw();
}

void player::Player::draw(Camera3D camera)
{
    BeginMode3D(camera);
    m_body->draw();
    EndMode3D();
}

Camera3D Player::getCamera()
{
    return m_camera;
}

player::Pistol::Pistol()
{
    m_state = PistolState::idle;
    m_cooldown = 0.0f;
    m_gun = LoadTexture("PIST2.png");
    m_frameRec = { 0.0f, 0.0f, m_gun.width / 5.0f, m_gun.height * 1.0f};
}

void player::Pistol::update()
{
    if (m_state == PistolState::idle)
    {
        // Gun is idle, can shoot
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            m_cooldown = 0.4f;
            m_state = PistolState::shoot1;
        }
    }
    else
    {
        // Gun is shooting
        m_cooldown -= GetFrameTime();
        if (m_cooldown > 0.33f)
        {
            m_state = PistolState::shoot1;
        }
        else if (m_cooldown > 0.28f)
        {
            m_state = PistolState::shoot2;
        }
        else if (m_cooldown > 0.2f)
        {
            m_state = PistolState::shoot3;
        }
        else if (m_cooldown > 0.13f)
        {
            m_state = PistolState::shoot4;
        }
        else if (m_cooldown <= 0.0f)
        {
            m_state = PistolState::idle;
            m_cooldown = 0.0f;
        }
        m_frameRec.x = m_state * m_gun.width / 5.0f;

    }

}

void player::Pistol::draw()
{
    DrawTextureRec(m_gun, m_frameRec, Vector2{ static_cast<float>(SCREEN_WIDTH - m_gun.width / 5.0f), static_cast<float>(SCREEN_HEIGHT - m_gun.height) }, WHITE);
}
