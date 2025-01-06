#include "button.h"

using namespace button;

button::Button::~Button()
{
}

void Button::draw()
{
    switch (m_state) {
    case hover:
        DrawRectangleRounded(m_button_rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, Fade(BUTTON_HOVER_COLOR, 0.6f));
        DrawRectangleRoundedLinesEx(m_button_rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, 5.0f, BUTTON_HOVER_COLOR);
        break;
    case midClick:
        DrawRectangleRounded(m_button_rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, Fade(BUTTON_MIDCLICK_COLOR, 0.6f));
        DrawRectangleRoundedLinesEx(m_button_rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, 5.0f, BUTTON_MIDCLICK_COLOR);
        break;
    default:
        DrawRectangleRounded(m_button_rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, Fade(BUTTON_DEFAULT_COLOR, 0.6f));
        DrawRectangleRoundedLinesEx(m_button_rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, 5.0f, BUTTON_DEFAULT_COLOR);
    }

    Font font = GetFontDefault();
    Vector2 textSize = MeasureTextEx(font, m_text.c_str(), 20, 0);
    int text_x = m_button_rec.x + m_button_rec.width / 2 - textSize.x / 2;
    int text_y = m_button_rec.y + m_button_rec.height / 2 - textSize.y / 2;
    DrawText(m_text.c_str(), text_x, text_y, 20, BLACK);
}

void Button::updateState()
{
    Vector2 mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, m_button_rec))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            m_state = midClick;
        }
        else
        {
            m_state = hover;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_state = ButtonState::clicked;
    }
    else
    {
        m_state = idle;
    }

}

bool button::Button::clicked()
{
    if (m_state == ButtonState::clicked)
    {
        return true;
    }
    else
    {
        return false;
    }
}


