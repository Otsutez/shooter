#include "game.h"

using namespace game;
using namespace button;

Game::Game()
{
	// Setup raylib
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shooter");
	SetTargetFPS(60);

	// Set game state
	m_running = true;
	m_state = GameState::lobby;
	m_player1 = new Player(Vector3{ PLAYER1_START_X, 0.0f, PLAYER1_START_Z });
	m_player2 = new Player(Vector3{ PLAYER2_START_X, 0.0f, PLAYER2_START_Z });
	m_map = new Map;
	m_bg = Color{ 102, 191, 255, 255 };
	m_crosshair = LoadTexture("crosshair007.png");
	float x = SCREEN_WIDTH / 2.0f - BUTTON_WIDTH / 2.0f;
	float play_y = SCREEN_HEIGHT / 2.0f - BUTTON_HEIGHT - BUTTON_SPACING / 2.0f;
	float quit_y = SCREEN_HEIGHT / 2.0f + BUTTON_SPACING / 2.0f;
	m_playButton = new Button{ x, play_y, BUTTON_WIDTH, BUTTON_HEIGHT, "PLAY" };
	m_quitButton = new Button{ x, quit_y, BUTTON_WIDTH, BUTTON_HEIGHT, "QUIT" };

	// Initialize lobby camera
	Camera3D camera{ 0 };
	camera.position = Vector3{ 9 * TILE_SIZE, 6 * TILE_SIZE, 9 * TILE_SIZE };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	m_lobbyCamera = camera;

	int sock = 0;
}

Game::~Game()
{
	delete m_playButton;
	delete m_quitButton;
	delete m_player1;
	delete m_player2;
	delete m_map;
	UnloadTexture(m_crosshair);
	CloseWindow();
}

void Game::run()
{
	while (is_running())
	{
		// Update game state
		if (m_state == GameState::lobby)
		{
			updateLobby();
		}
		else
		{
			updatePlay();
		}

		// Draw
		BeginDrawing();
		ClearBackground(m_bg);
		if (m_state == GameState::lobby)
		{
			drawLobby();
		}
		else
		{
			drawPlay();
		}
		EndDrawing();
	}
}

bool Game::is_running()
{
	return !WindowShouldClose() && m_running;
}

void Game::updateLobby()
{
	// Update lobby camera
	UpdateCamera(&m_lobbyCamera, CAMERA_ORBITAL);

	// Update button states to deteck clicking
	m_playButton->updateState();
	m_quitButton->updateState();

	if (m_quitButton->clicked())
	{
		// Quit game because quit button was clicked
		m_running = false;
	}

	if (m_playButton->clicked()) {
		// Start game and change game state

		m_state = GameState::play;
		DisableCursor();
	}
}

void Game::drawLobby()
{
	// Draw rotating map
	BeginMode3D(m_lobbyCamera);
	m_map->draw(m_lobbyCamera);
	m_player1->draw(m_lobbyCamera);
	m_player2->draw(m_lobbyCamera);
	EndMode3D();

	m_playButton->draw();
	m_quitButton->draw();
}

void Game::updatePlay()
{
	m_player1->update(m_map->getObjects());

}

void Game::drawPlay()
{
	m_map->draw(m_player1->getCamera());
	m_player1->draw();
	m_player2->draw(m_player1->getCamera());

	// Draw crosshair
	DrawTexture(m_crosshair, SCREEN_WIDTH / 2 - m_crosshair.width / 2, SCREEN_HEIGHT / 2 - m_crosshair.height / 2, RAYWHITE);
}


