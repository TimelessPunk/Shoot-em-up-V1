#include "Player.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Player::Player(const sf::Texture& texture)
    : m_sprite(texture) //  obligatoire SFML 3
{
    // Origin au centre
    m_sprite.setOrigin(sf::Vector2f(
        texture.getSize().x * 0.5f,
        texture.getSize().y * 0.5f
    ));

    // Position au centre de l'écran
    m_sprite.setPosition(sf::Vector2f(400.f, 300.f));
}

void Player::Update(float)
{
    // movement plus tard
}

void Player::Render(sf::RenderTarget& target)
{
    target.draw(m_sprite);
}
