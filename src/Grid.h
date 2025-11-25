#pragma once

#ifndef GRID_H
#define GRID_H

#include <map>
#include <string>
#include <vector>

#include "SFML/Graphics/Color.hpp"

#include "GameEntity.h"
#include "TileObject.h"

namespace game
{
	using namespace core;

	class Grid : public GameEntity
	{
	public:

		Grid();
		Grid(int _width, int _height, bool _useRandomSeed = true, std::string _seed = std::to_string(_TIME));
		Grid(const Grid& that, GameEntity* _gameObject);
		~Grid();

		Grid* Clone(GameEntity* _gameObject) override;

		void Init() override;

		void Start() override;
		void Update(float _elapsedTime) override;

		int width = 2, height = 2;
		int index(int _x, int _y) const { return _x + width * _y; }

		TileObject* GetTile(int _x, int _y);

		GameEntity* tilePrefab = nullptr;
		std::vector<TileObject*> tiles;

		Color backgroundColor;
		Camera* camera;

	private:

		void GenerateMap();

		void GenerateTerritory();
		void GenerateIsland();
		void CalculateBiomes();
		void GenerateBiomes();
		void CreateMap();

		std::map<std::pair<int, int>, int> SmoothArea(std::map<std::pair<int, int>, int>& _area);
		int GetSurroundingTiles(int _x, int _y, std::map<std::pair<int, int>, int>& _area);

		void SmoothBiomes();
		void CheckBiome(int _x, int _y);

		void CreateSeaAndLakeRegions();

		void CreateTile(int _x, int _y, BiomeType _b);

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
