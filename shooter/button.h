#pragma once
#include "raylib.h"
#include <string>
#include "config.h"

using std::string;

namespace button {
	enum ButtonState {
		idle,
		hover,
		midClick,
		clicked
	};

	class Button {
	public:
		// Constructor that accept rectangle
		Button(Rectangle rec, string text) :
			m_button_rec{ rec },
			m_text{ text } {
		}

		// Constructor that accepts rectangle details
		Button(float x, float y, float width, float height, string text) :
			m_button_rec{ Rectangle {x, y, width, height} },
			m_text{ text } {
		}

		~Button();
		void draw();
		void updateState();
		bool clicked();

	private:
		Rectangle m_button_rec;
		string m_text;
		ButtonState m_state{ idle };
	};
}