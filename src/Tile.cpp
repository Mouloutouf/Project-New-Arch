#include "Tile.h"

#include "SFML/Graphics/Texture.hpp"

namespace game
{
	Tile::Tile()
	{
	}
	Tile::Tile(const std::string& _spritePath, sf::Vector2i _position, BiomeType _biomeType)
		: gridPosition(_position), biomeType(_biomeType)
	{
		CreateSprite(_spritePath);
	}

	void Tile::CreateSprite(const std::string& _spritePath)
	{
		if (_spritePath.empty() == false) {
			auto texture = sf::Texture();
			if (texture.loadFromFile(_spritePath))
				sprite = std::make_unique<sf::Sprite>(texture);
		}
	}

	void Tile::Start()
	{
	}
	void Tile::Update(float _elapsedTime)
	{
	}
	void Tile::EventUpdate(sf::Event& _event, float _elapsedTime)
	{
	}
}
