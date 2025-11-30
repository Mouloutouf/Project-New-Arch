//
// Created by maxdu on 30/11/2025.
//

#ifndef NEWARCH_SPRITEOBJECT_H
#define NEWARCH_SPRITEOBJECT_H

#include <string>
#include <vector>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Layers.h"

class SpriteObject
{
public:
    SpriteObject();
    SpriteObject(int _ppu, std::string _spritePath);
    SpriteObject(int _ppu, sf::Texture _texture);
    virtual ~SpriteObject();

    int ppu = 100;

    int layer = DEFAULT_LAYER;
    int orderInLayer = 0;

    bool render = true;

    std::vector<sf::Drawable*> drawables;

    void Create(std::string _spritePath);
    void Create(sf::Texture _texture);

    std::string spritePath;

    sf::Texture texture;
    sf::Sprite sprite;

    void SetSprite(std::string _spritePath);
    void SetSprite(sf::Texture _texture);

    sf::Vector2f GetSize();
};

#endif //NEWARCH_SPRITEOBJECT_H