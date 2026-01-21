#include "MenuScene.hpp"

#include "Application.hpp"
#include "Resources.hpp"
#include "Input.hpp"
#include "SceneManager.hpp"

#include "PlayScene.hpp"
#include "OptionsScene.hpp"


#include <string>

// --------------------------------------------------
// Utils
// --------------------------------------------------
static sf::Vector2f CenterX(const sf::Text& t, float y, float w)
{
    const sf::FloatRect b = t.getLocalBounds(); // SFML 3
    return sf::Vector2f(
        (w * 0.5f) - (b.size.x * 0.5f) - b.position.x,
        y
    );
}

// --------------------------------------------------
// Scene
// -------------------------------------------------
void MenuScene::OnEnter(eng::Application& app)
{
    const auto winSize = app.Window().getSize();
    const float W = static_cast<float>(winSize.x);
    const float H = static_cast<float>(winSize.y);

    // ---------- Background ----------
    m_bgTex = &app.Resources().GetTexture("Assets/Textures/player.png");
    m_bg.emplace(*m_bgTex);

    const auto texSize = m_bgTex->getSize();
    if (texSize.x > 0 && texSize.y > 0)
    {
        m_bg->setScale(sf::Vector2f(
            static_cast<float>(winSize.x) / static_cast<float>(texSize.x),
            static_cast<float>(winSize.y) / static_cast<float>(texSize.y)
        ));
    }

    // ---------- Font ----------
    m_font = &app.Resources().GetFont("Assets/Fonts/cinzel.ttf");

    // ---------- Layout ----------
    const float titleY = H * 0.18f;
    const float menuStartY = H * 0.48f;
    const float spacing = 70.f;

    // ---------- Title ----------
    m_title.emplace(*m_font);              // ⚠️ PAS de ctor par défaut
    m_title->setCharacterSize(80);
    m_title->setString("MEDIEVAL");
    m_title->setPosition(CenterX(*m_title, titleY, W));

    // ---------- Menu items ----------
    const char* labels[3] = { "COMMENCER", "OPTIONS", "QUITTER" };

    for (int i = 0; i < 3; ++i)
    {
        m_items[i].emplace(*m_font);       // ⚠️ PAS de ctor par défaut
        m_items[i]->setCharacterSize(46);
        m_items[i]->setString(labels[i]);
        m_items[i]->setPosition(
            CenterX(*m_items[i], menuStartY + i * spacing, W)
        );
    }

    m_selected = 0;
    RefreshTexts();
}

void MenuScene::Update(eng::Application& app, float)
{
    auto& input = app.GetInput();

    if (input.Pressed(sf::Keyboard::Key::Up))
    {
        m_selected = (m_selected + 2) % 3;
        RefreshTexts();
    }

    if (input.Pressed(sf::Keyboard::Key::Down))
    {
        m_selected = (m_selected + 1) % 3;
        RefreshTexts();
    }

    if (input.Pressed(sf::Keyboard::Key::Enter))
    {
        Activate(app);
    }
}

void MenuScene::Render(eng::Application&, sf::RenderTarget& target)
{
    if (m_bg)     target.draw(*m_bg);
    if (m_title)  target.draw(*m_title);

    for (int i = 0; i < 3; ++i)
        if (m_items[i])
            target.draw(*m_items[i]);
}

// --------------------------------------------------
// Helpers
// --------------------------------------------------
void MenuScene::RefreshTexts()
{
    const char* base[3] = { "COMMENCER", "OPTIONS", "QUITTER" };

    for (int i = 0; i < 3; ++i)
    {
        if (!m_items[i]) continue;

        std::string s = base[i];
        if (i == m_selected)
            s = "> " + s;

        m_items[i]->setString(s);
        m_items[i]->setStyle(
            i == m_selected ? sf::Text::Bold : sf::Text::Regular
        );
    }
}

void MenuScene::Activate(eng::Application& app)
{
    if (m_selected == 0)
    {
        app.Scenes().Set(std::make_unique<PlayScene>(), app);
    }
    else if (m_selected == 1)
    {
        app.Scenes().Set(std::make_unique<OptionsScene>(), app);
    }
    else
    {
        app.Quit();
    }
}
