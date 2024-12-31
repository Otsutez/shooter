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
		// Update
		m_state->update(*this);
		// Draw
		BeginDrawing();
		ClearBackground(WHITE);
		m_state->draw(*this);
		EndDrawing();
	}
}

bool game::Game::is_running()
{
	return !WindowShouldClose() && m_running;
}

void game::Game::set_running(bool val)
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

void LobbyState::update(Game& game)
{
	// Update button states to deteck clicking
	m_playButton->updateState();
	m_quitButton->updateState();

	if (m_quitButton->clicked())
	{
		// Quit game because quit button was clicked
		game.set_running(false);
	}
}

void game::LobbyState::draw(Game& game)
{
	m_playButton->draw();
	m_quitButton->draw();
}

void game::PlayState::update(Game& game)
{
}

void game::PlayState::draw(Game& game)
{
}
