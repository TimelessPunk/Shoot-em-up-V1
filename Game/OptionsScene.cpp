#include "OptionsScene.hpp"
#include "MenuScene.hpp"
#include "Application.hpp"
#include "GameSettings.hpp"
#include <algorithm>
#include <iostream>


void OptionsScene::OnEnter(eng::Application& app)
{
    // Charger le fond
    if (!m_backgroundTexture.loadFromFile("Assets/Textures/player.png"))
    {
        std::cerr << "Erreur : impossible de charger le fond" << std::endl;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    // Adapter la taille à la fenêtre
    sf::Vector2u windowSize = app.Window().getSize();
    sf::Vector2u texSize = m_backgroundTexture.getSize();

    m_backgroundSprite.setScale(sf::Vector2f(
        static_cast<float>(windowSize.x) / static_cast<float>(texSize.x),
        static_cast<float>(windowSize.y) / static_cast<float>(texSize.y)
    ));

    // Résolutions disponibles
    m_resolutions = { {1280, 720}, {1600, 900}, {1920, 1080} };
    m_resolutionIndex = 0;

    // Police
    m_font = &app.Resources().GetFont("Assets/Fonts/cinzel.ttf");

    // Titre
    m_title.emplace(*m_font);
    m_title->setCharacterSize(72);
    m_title->setString("OPTIONS");
    m_title->setPosition({ 100.f, 50.f });

    // Options
    for (int i = 0; i < (int)OptionItem::Count; ++i)
    {
        m_items[i].emplace(*m_font);
        m_items[i]->setCharacterSize(48);
        m_items[i]->setPosition({ 100.f, 150.f + i * 60.f });
    }

    RefreshTexts();
}

void OptionsScene::Update(eng::Application& app, float dt)
{
    auto& input = app.GetInput();

    // Navigation du menu
    if (input.Pressed(sf::Keyboard::Key::Up))
    {
        int sel = static_cast<int>(m_selected);
        sel = (sel + static_cast<int>(OptionItem::Count) - 1) % static_cast<int>(OptionItem::Count);
        m_selected = static_cast<OptionItem>(sel);
    }

    if (input.Pressed(sf::Keyboard::Key::Down))
    {
        int sel = static_cast<int>(m_selected);
        sel = (sel + 1) % static_cast<int>(OptionItem::Count);
        m_selected = static_cast<OptionItem>(sel);
    }

    // Modifier les valeurs
    if (input.Pressed(sf::Keyboard::Key::Left))
    {
        switch (m_selected)
        {
        case OptionItem::Volume:
            GameSettings::Get().volume = std::max(0, GameSettings::Get().volume - 5);
            break;
        case OptionItem::Brightness:
            GameSettings::Get().brightness = std::max(50, GameSettings::Get().brightness - 5);
            break;
        case OptionItem::Resolution:
        {
            int size = static_cast<int>(m_resolutions.size());
            m_resolutionIndex = (m_resolutionIndex + size - 1) % size;
            GameSettings::Get().resolution = m_resolutions[m_resolutionIndex];
            break;
        }
        default: break;
        }
    }

    if (input.Pressed(sf::Keyboard::Key::Right))
    {
        switch (m_selected)
        {
        case OptionItem::Volume:
            GameSettings::Get().volume = std::min(100, GameSettings::Get().volume + 5);
            break;
        case OptionItem::Brightness:
            GameSettings::Get().brightness = std::min(150, GameSettings::Get().brightness + 5);
            break;
        case OptionItem::Resolution:
        {
            int size = static_cast<int>(m_resolutions.size());
            m_resolutionIndex = (m_resolutionIndex + 1) % size;
            GameSettings::Get().resolution = m_resolutions[m_resolutionIndex];
            break;
        }
        default: break;
        }
    }

    // Retour menu
    if (input.Pressed(sf::Keyboard::Key::Enter) || input.Pressed(sf::Keyboard::Key::Escape))
    {
        app.Scenes().Set(std::make_unique<MenuScene>(), app);
    }

    RefreshTexts();
}

void OptionsScene::Render(eng::Application& app, sf::RenderTarget& target)
{
    target.draw(m_backgroundSprite);

    if (m_title) target.draw(*m_title);

    for (int i = 0; i < (int)OptionItem::Count; ++i)
    {
        if (m_items[i]) target.draw(*m_items[i]);
    }
}

void OptionsScene::RefreshTexts()
{
    const char* labels[] = { "Volume", "Luminosite", "Resolution", "RETOUR" };

    for (int i = 0; i < (int)OptionItem::Count; ++i)
    {
        std::string valueStr;

        switch (static_cast<OptionItem>(i))
        {
        case OptionItem::Volume:
            valueStr = std::to_string(GameSettings::Get().volume) + " %";
            break;
        case OptionItem::Brightness:
            valueStr = std::to_string(GameSettings::Get().brightness) + " %";
            break;
        case OptionItem::Resolution:
        {
            auto r = m_resolutions[m_resolutionIndex];
            valueStr = std::to_string(r.x) + " x " + std::to_string(r.y);
            break;
        }
        default: break;
        }

        std::string text = labels[i];
        if (!valueStr.empty()) text += " : " + valueStr;
        if (i == static_cast<int>(m_selected)) text = "> " + text;

        m_items[i]->setString(text);
    }
}
