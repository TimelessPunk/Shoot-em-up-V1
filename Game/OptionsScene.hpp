#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <string>
#include <memory>
#include "Scene.hpp"
#include "Application.hpp"
#include "GameSettings.hpp"
#include "MenuScene.hpp"

class OptionsScene : public eng::Scene
{
public:
    OptionsScene() = default;

    void OnEnter(eng::Application& app) override;
    void Update(eng::Application& app, float dt) override;
    void Render(eng::Application& app, sf::RenderTarget& target) override;

private:
    const sf::Font* m_font = nullptr;
    std::optional<sf::Text> m_title;

    enum class OptionItem { Volume, Brightness, Resolution, Back, Count };
    OptionItem m_selected = OptionItem::Volume;

    int m_resolutionIndex = 0;
    std::vector<sf::Vector2u> m_resolutions;

    std::optional<sf::Text> m_items[(int)OptionItem::Count];

    void RefreshTexts();

    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite; // <-- objet direct, pas de smart pointer

};
