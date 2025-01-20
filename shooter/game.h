#pragma once
#include <string>
#include "raylib.h"
#include "button.h"
#include "config.h"
#include "player.h"
#include "map.h"

using button::Button;
using button::InputBox;
using player::Player;
using map::Map;

namespace game {
	
	enum class GameState {
		lobby,
		play
	};

	class Game {
	public:
		Game();
		~Game();
		void run();
		bool is_running();
		void updateLobby();
		void drawLobby();
		void updatePlay();
		void drawPlay();

	private:
		bool m_running;
		GameState m_state;
		Camera3D m_lobbyCamera;
		Button* m_playButton;
		Button* m_quitButton;
		Player* m_player1;
		Player* m_player2;
		Map* m_map;
		Color m_bg;
		Texture2D m_crosshair;
		int sock;
	};
};
