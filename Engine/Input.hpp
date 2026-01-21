#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cstddef>

namespace eng
{
    class Input
    {
    public:
        void BeginFrame()
        {
            m_pressed.fill(false);
            m_released.fill(false);
        }

        void OnKeyPressed(sf::Keyboard::Key key)
        {
            const auto i = static_cast<std::size_t>(key);
            if (i >= KeyCount) return;
            if (!m_down[i]) m_pressed[i] = true;
            m_down[i] = true;
        }

        void OnKeyReleased(sf::Keyboard::Key key)
        {
            const auto i = static_cast<std::size_t>(key);
            if (i >= KeyCount) return;
            m_down[i] = false;
            m_released[i] = true;
        }

        bool Down(sf::Keyboard::Key key) const
        {
            const auto i = static_cast<std::size_t>(key);
            return (i < KeyCount) ? m_down[i] : false;
        }

        bool Pressed(sf::Keyboard::Key key) const
        {
            const auto i = static_cast<std::size_t>(key);
            return (i < KeyCount) ? m_pressed[i] : false;
        }

    private:
        static constexpr std::size_t KeyCount = 256;
        std::array<bool, KeyCount> m_down{};
        std::array<bool, KeyCount> m_pressed{};
        std::array<bool, KeyCount> m_released{};
    };
}
