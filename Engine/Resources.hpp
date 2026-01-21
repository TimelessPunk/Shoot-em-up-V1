#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

namespace eng
{
    class ResourceManager
    {
    public:
        const sf::Texture& GetTexture(const std::string& path)
        {
            auto it = m_textures.find(path);
            if (it != m_textures.end())
                return *it->second;

            auto tex = std::make_unique<sf::Texture>();
            if (!tex->loadFromFile(path))
                throw std::runtime_error("Failed to load texture: " + path);

            const sf::Texture& ref = *tex;
            m_textures.emplace(path, std::move(tex));
            return ref;
        }

        // SFML 3: Font -> openFromFile
        const sf::Font& GetFont(const std::string& path)
        {
            auto it = m_fonts.find(path);
            if (it != m_fonts.end())
                return *it->second;

            auto font = std::make_unique<sf::Font>();
            if (!font->openFromFile(path))
                throw std::runtime_error("Failed to load font: " + path);

            const sf::Font& ref = *font;
            m_fonts.emplace(path, std::move(font));
            return ref;
        }

        void Clear()
        {
            m_textures.clear();
            m_fonts.clear();
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
    };
}
