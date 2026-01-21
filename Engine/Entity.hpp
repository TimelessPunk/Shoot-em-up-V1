#pragma once
#include <SFML/Graphics.hpp>

namespace eng
{
    class Entity
    {
    public:
        virtual ~Entity() = default;
        virtual void Update(float dt) = 0;
        virtual void Render(sf::RenderTarget& target) = 0;
        virtual sf::FloatRect GetBounds() const = 0;

        bool IsAlive() const { return m_alive; }
        void Kill() { m_alive = false; }

    private:
        bool m_alive{ true };
    };
}
