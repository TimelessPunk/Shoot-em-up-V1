#pragma once

#include "Engine/Scene.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <optional>
#include <array>

class MenuScene : public eng::Scene
{
public:
    MenuScene() = default;
    ~MenuScene() override = default;

    void OnEnter(eng::Application& app) override;
    void Update(eng::Application& app, float dt) override;
    void Render(eng::Application& app, sf::RenderTarget& target) override;

private:
    void RefreshTexts();
    void Activate(eng::Application& app);

private:
    // Background
    const sf::Texture* m_bgTex{ nullptr };
    std::optional<sf::Sprite> m_bg;

    // Text
    const sf::Font* m_font{ nullptr };
    std::optional<sf::Text> m_title;
    std::array<std::optional<sf::Text>, 3> m_items;

    int m_selected{ 0 };
};
