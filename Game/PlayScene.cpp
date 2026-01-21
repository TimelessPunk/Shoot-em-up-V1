#include "PlayScene.hpp"
#include "Application.hpp"
#include "Input.hpp"

void PlayScene::OnEnter(eng::Application&)
{
    m_player.setSize({ 60.f, 60.f });
    m_player.setOrigin({ 30.f, 30.f });
    m_player.setPosition({ 300.f, 300.f });
}

void PlayScene::Update(eng::Application& app, float dt)
{
    auto& in = app.GetInput();

    sf::Vector2f dir{ 0.f, 0.f };
    if (in.Down(sf::Keyboard::Key::Left))  dir.x -= 1.f;
    if (in.Down(sf::Keyboard::Key::Right)) dir.x += 1.f;
    if (in.Down(sf::Keyboard::Key::Up))    dir.y -= 1.f;
    if (in.Down(sf::Keyboard::Key::Down))  dir.y += 1.f;

    const float speed = 300.f;
    m_player.move(dir * (speed * dt));
}

void PlayScene::Render(eng::Application&, sf::RenderTarget& target)
{
    target.draw(m_player);
}
