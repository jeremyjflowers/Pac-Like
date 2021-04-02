#include "KeyboardBehavior.h"
#include "raylib.h"
#include <Vector2.h>

void KeyboardBehavior::update(Agent* owner, float deltaTime)
{
    if (IsKeyDown(KEY_UP))
        owner->setVelocity({ 0.0f, -m_speedIncrement });
    if (IsKeyDown(KEY_DOWN))
        owner->setVelocity({ 0.0f, m_speedIncrement });
    if (IsKeyDown(KEY_LEFT))
        owner->setVelocity({ -m_speedIncrement, 0.0f });
    if (IsKeyDown(KEY_RIGHT))
        owner->setVelocity({ m_speedIncrement, 0.0f });
}
