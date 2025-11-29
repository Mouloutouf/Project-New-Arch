#pragma once

#ifndef GRID_H
#define GRID_H

#include <map>
#include <string>
#include <vector>

#include "SFML/Graphics/Color.hpp"

#include "Utility.h"
#include "GameEntity.h"
#include "Tile.h"

namespace game
{
	using namespace core;

	class Grid : public GameEntity
	{
	public:

		Grid(int _width, int _height, bool _useRandomSeed = true, const std::string& _seed = std::to_string(CURRENT_TIME));

		void Start() override;
		void Update(float _elapsedTime) override;

		int width = 2, height = 2;
		int index(const int _x, const int _y) const { return _x + width * _y; }

		Tile* GetTile(int _x, int _y) const;

		std::vector<Tile*> tiles;

		sf::Color backgroundColor;

	private:
		void GenerateMap();

		void GenerateTerritory();
		void GenerateIsland();
		void CalculateBiomes();
		void GenerateBiomes();
		void CreateMap();

		std::map<std::pair<int, int>, int> SmoothArea(std::map<std::pair<int, int>, int>& _inputArea) const;

		static int GetSurroundingTiles(int _x, int _y, std::map<std::pair<int, int>, int>& _area);

		void SmoothBiomes();
		void CheckBiome(int _x, int _y);

		void CreateSeaAndLakeRegions();

		void CreateTile(int _x, int _y, BiomeType _biomeType);

		int randomTerritoryPercent;
		std::map<std::pair<int, int>, int> territoryTiles;

		int randomIslandPercent;
		std::map<std::pair<int, int>, int> islandTiles;

		std::vector<BiomeType> preTiles;

		std::map<BiomeType, float> biomesFillValues;
		std::map<BiomeType, float> biomesFillPercent;

		std::string seed;
		bool useRandomSeed = true;
	};
}

#endif // !GRID_H
