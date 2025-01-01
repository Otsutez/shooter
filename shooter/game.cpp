#include "game.h"

using namespace game;
using namespace button;

Game::~Game()
{
	delete m_state;
	CloseWindow();
}

void Game::run()
{
	while (is_running()) {
		// Check if state needs to be update
		GameState* new_state = m_state->update(*this);
		if (new_state)
		{
			delete m_state;
			m_state = new_state;
			m_state->enter();
		}

		// Draw
		BeginDrawing();
		ClearBackground(SKYBLUE);
		m_state->draw(*this);
		EndDrawing();
	}
}

bool Game::is_running()
{
	return !WindowShouldClose() && m_running;
}

void Game::set_running(bool val)
{
	m_running = val;
}

// LobbyState implementations
LobbyState::LobbyState()
{
	float x = SCREEN_WIDTH / 2.0f - BUTTON_WIDTH / 2.0f;
	float play_y = SCREEN_HEIGHT / 2.0f - BUTTON_HEIGHT - BUTTON_SPACING / 2.0f;
	float quit_y = SCREEN_HEIGHT / 2.0f + BUTTON_SPACING / 2.0f;
	m_playButton = new Button{ x, play_y, BUTTON_WIDTH, BUTTON_HEIGHT, "PLAY" };
	m_quitButton = new Button{ x, quit_y, BUTTON_WIDTH, BUTTON_HEIGHT, "QUIT" };
}

GameState* LobbyState::update(Game& game)
{
	// Update button states to deteck clicking
	m_playButton->updateState();
	m_quitButton->updateState();

	if (m_quitButton->clicked())
	{
		// Quit game because quit button was clicked
		game.set_running(false);
	}

	if (m_playButton->clicked()) {
		// Start game and change game state
		return new PlayState;
	}

	return nullptr;
}

void LobbyState::draw(Game& game)
{
	m_playButton->draw();
	m_quitButton->draw();
}

void LobbyState::enter()
{
	// Do nothing
}

LobbyState::~LobbyState()
{
	delete m_playButton;
	delete m_quitButton;
}

game::PlayState::PlayState()
{
	m_player = new Player;
	m_map = new Map;
}

GameState* PlayState::update(Game& game)
{
	// Update player camera
	m_player->update();
	return nullptr;
}

void PlayState::draw(Game& game)
{
	BeginMode3D(m_player->m_camera);
	m_map->draw();
	EndMode3D();
}

void PlayState::enter()
{
	DisableCursor();
}

