#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Animation SFML 3.0.2");

    sf::Texture texture;
    texture.loadFromFile("professor.png");

    const int frameWidth = 64;
    const int frameHeight = 64;

    AnimatedSprite anim(texture, frameWidth, frameHeight);
    anim.setPosition(300.f, 200.f);

    // ---- Animations (9 frames × 4 lignes) ----
    Animation idle = { 0, 9, 0.10f };
    Animation atk = { 1, 9, 0.08f };
    Animation magic = { 2, 9, 0.08f };
    Animation walk = { 3, 9, 0.12f };

    anim.play(idle);

    sf::Clock clock;

    while (window.isOpen())
    {
        std::optional<sf::Event> event;
        while (window.pollEvent())
        {
            if ((event && event->is<sf::Event::Closed>()))
                window.close();
        }

        // ----------- Contrôles SFML 3.0.2 -----------
        using K = sf::Keyboard::Key;

        if (sf::Keyboard::isKeyPressed(K::D))
            anim.play(walk);
        else if (sf::Keyboard::isKeyPressed(K::Q))
            anim.play(atk);
        else if (sf::Keyboard::isKeyPressed(K::S))
            anim.play(magic);
        else
            anim.play(idle);

        float dt = clock.restart().asSeconds();
        anim.update(dt);

        window.clear();
        anim.draw(window);
        window.display();
    }
}
