/*
* We implement our Game object using the state design pattern.
* https://gameprogrammingpatterns.com/state.html
*/

#pragma once
#include <string>
#include "raylib.h"
#include "button.h"
#include "config.h"

using button::Button;

namespace game {
	class Game;

	// Game state interface
	class GameState
	{
	public:
		virtual ~GameState() {}
		virtual void update(Game& game) {}
		virtual void draw(Game& game) {}
	};

	// Lobby state class
	class LobbyState : public GameState
	{
	public:
		LobbyState();
		virtual void update(Game& game);
		virtual void draw(Game& game);

	private:
		Button* m_playButton;
		Button* m_quitButton;
	};

	// Play state class
	class PlayState : public GameState
	{
		PlayState();
		virtual void update(Game& game);
		virtual void draw(Game& game);
	};

	// Game class
	class Game {
	public:
		Game() :
			m_state{ new LobbyState },
			m_running{ true }
		{
			InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shooter");
			SetTargetFPS(60);
		}
		~Game();
		void run();
		bool is_running();
		void set_running(bool val);

	private:
		GameState* m_state{ new LobbyState };
		bool m_running{ true };
	};
};
