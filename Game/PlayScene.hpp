#pragma once
#include "Scene.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class PlayScene : public eng::Scene
{
public:
    void OnEnter(eng::Application& app) override;
    void Update(eng::Application& app, float dt) override;
    void Render(eng::Application& app, sf::RenderTarget& target) override;

private:
    sf::RectangleShape m_player;
};
