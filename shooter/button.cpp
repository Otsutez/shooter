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
    int text_x = (int) (m_button_rec.x + m_button_rec.width / 2 - textSize.x / 2);
    int text_y = (int) (m_button_rec.y + m_button_rec.height / 2 - textSize.y / 2);
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

button::InputBox::InputBox(Rectangle rec)
{
    m_rec = rec;
    m_text = "";
}

void button::InputBox::update()
{
    if (CheckCollisionPointRec(GetMousePosition(), m_rec))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (m_text.size() < MAX_INPUT_CHARS))
            {
                m_text.push_back(key);
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (m_text.size() != 0)
            {
                m_text.pop_back();
            }
        }
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void button::InputBox::draw()
{
    bool mouseOnText = CheckCollisionPointRec(GetMousePosition(), m_rec);
    
    DrawRectangleRec(m_rec, RAYWHITE);

    if (mouseOnText)
    {
        DrawRectangleLines((int)m_rec.x, (int)m_rec.y, (int)m_rec.width, (int)m_rec.height, RED);
    }
    else
    {
        DrawRectangleLines((int)m_rec.x, (int)m_rec.y, (int)m_rec.width, (int)m_rec.height, DARKGRAY);
    }
    
    DrawText(m_text.c_str(), (int)m_rec.x + 5, (int)m_rec.y + 8, 40, MAROON);

    if (mouseOnText)
    {
        DrawText("_", (int)m_rec.x + 8 + MeasureText(m_text.c_str(), 40), (int)m_rec.y + 12, 40, MAROON);
    }
}

string button::InputBox::getAddress()
{
    return m_text;
}
