#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace eng { class Application; }

class Player
{
public:
    explicit Player(const sf::Texture& texture);

    void Update(float dt);
    void Render(sf::RenderTarget& target);

private:
    sf::Sprite m_sprite; // ✅ OK car construit dans le ctor
};
