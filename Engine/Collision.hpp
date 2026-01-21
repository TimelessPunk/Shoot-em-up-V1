#pragma once
#include <SFML/Graphics.hpp>

namespace eng
{
    inline bool Intersects(const sf::FloatRect& a, const sf::FloatRect& b)
    {
        return a.findIntersection(b).has_value();
    }
}
