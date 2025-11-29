#pragma once

#ifndef TILE_H
#define TILE_H

#include <map>
#include <memory>

#include "SFML/Graphics/Sprite.hpp"

#include "Enums.h"
#include "GameEntity.h"

namespace game
{
	using namespace core;

	class Tile : public GameEntity
	{
	public:
		Tile();
		Tile(const std::string& _spritePath, sf::Vector2i _position, BiomeType _biomeType);

		void CreateSprite(const std::string& _spritePath);

		void Start() override;
		void Update(float _elapsedTime) override;
		void EventUpdate(sf::Event& _event, float _elapsedTime) override;

		sf::Vector2i gridPosition;

		BiomeType biomeType = BiomeType::None;
		TerrainType terrainType = TerrainType::Normal;

		std::map<ResourceType, int> resources;

		std::unique_ptr<sf::Sprite> sprite;
	};
}

#endif // !TILE_H
