#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class AnimatedSprite {
public:
    AnimatedSprite(sf::Texture& tex, int frameW, int frameH)
        : texture(tex), width(frameW), height(frameH), sprite{ tex } // initialisation directe
    {
    }

    void play(const Animation& anim) {
        if (&anim != currentAnimation) {
            currentAnimation = &anim;
            currentFrame = 0;
            timer = 0.f;
        }
    }

    void update(float dt) {
        if (!currentAnimation) return;

        timer += dt;
        if (timer >= currentAnimation->frameTime) {
            timer = 0.f;
            currentFrame = (currentFrame + 1) % currentAnimation->frameCount;
        }

        sf::IntRect rect(
            sf::Vector2i{ currentFrame * width, currentAnimation->row * height },
            sf::Vector2i{ width, height }
        );

        sprite.setTextureRect(rect);
    }


    void draw(sf::RenderWindow& w) { w.draw(sprite); }

    void setPosition(float x, float y) { sprite.setPosition(sf::Vector2f{ x, y }); }

private:
    sf::Texture& texture;
    sf::Sprite sprite;
    int width, height;

    const Animation* currentAnimation = nullptr;
    int currentFrame = 0;
    float timer = 0.f;
};
