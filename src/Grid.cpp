#include "Grid.h"

#include <random>

#include "SFML/System/Vector2.hpp"

#include "Biomes.h"
#include "Utility.h"

namespace game
{
	Grid::Grid(const int _width, const int _height, const bool _useRandomSeed, const std::string& _seed)
		: width(_width), height(_height), seed(_seed), useRandomSeed(_useRandomSeed)
	{
		backgroundColor = sf::Color(1, 9, 12);

		randomTerritoryPercent = 70; // Amount of Territory within the total Grid area (Sea biome by default)
		randomIslandPercent = 70; // Amount of Land within the total Territory area

		biomesFillValues.insert({ BiomeType::Desert, 3.5f });
		biomesFillValues.insert({ BiomeType::Field, 3.5f });
		biomesFillValues.insert({ BiomeType::Forest, 4.0f });
		biomesFillValues.insert({ BiomeType::Mountain, 2.0f });
		biomesFillValues.insert({ BiomeType::Lake, 2.0f });
	}

	void Grid::Start()
	{
		GenerateMap();
	}

	void Grid::Update(float _elapsedTime)
	{
	}

	Tile* Grid::GetTile(const int _x, const int _y) const
	{
		if (_x < 0 || _x >= width || _y < 0 || _y >= height) return nullptr;
		return tiles[index(_x, _y)];
	}

	void Grid::GenerateMap()
	{
		GenerateTerritory();

		GenerateIsland();

		CalculateBiomes();

		GenerateBiomes();

		CreateMap();
	}

	void Grid::GenerateTerritory()
	{
		std::random_device rd;
		std::mt19937 mt(rd());

		std::uniform_int_distribution dist(0, 99);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
					territoryTiles[{x, y}] = 0;
					continue;
				}

				const int randomPercent = dist(mt);
				territoryTiles[{x, y}] = randomPercent > randomTerritoryPercent ? 0 : 1;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			territoryTiles = SmoothArea(territoryTiles);
		}
	}

	void Grid::GenerateIsland()
	{
		std::random_device rd;
		std::mt19937 mt(rd());

		std::uniform_int_distribution dist(0, 99);

		preTiles = std::vector<BiomeType>(static_cast<size_t>(width) * height);

		for (auto& [pos, territory] : territoryTiles)
		{
			int sx = pos.first, sy = pos.second;

			if (territory == 0) {
				preTiles[index(sx, sy)] = BiomeType::None;
			}
			else {
				if (GetSurroundingTiles(sx, sy, territoryTiles) < 8) {
					islandTiles[{sx, sy}] = 0;
					continue;
				}

				const int randomPercent = dist(mt);

				islandTiles[{sx, sy}] = randomPercent > randomIslandPercent ? 0 : 1;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			islandTiles = SmoothArea(islandTiles);
		}
	}

	std::map<std::pair<int, int>, int> Grid::SmoothArea(std::map<std::pair<int, int>, int>& _inputArea) const
	{
		std::map<std::pair<int, int>, int> outputArea = _inputArea;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				if (_inputArea.count({ x, y }))
				{
					const int surroundingTiles = GetSurroundingTiles(x, y, _inputArea);

					if (surroundingTiles > 4) {
						outputArea[{x, y}] = 1;
					}
					else if (surroundingTiles < 4) {
						outputArea[{x, y}] = 0;
					}
				}
			}
		}

		return outputArea;

		/*for (auto& at : _inputArea)
			{
				int ax = at.first.first, ay = at.first.second;

				int surroundingTiles = GetSurroundingTiles(ax, ay, _inputArea);

				if (surroundingTiles > 4) {
					at.second = 1;
				}
				else if (surroundingTiles < 4) {
					at.second = 0;
				}
			}*/
	}
	int Grid::GetSurroundingTiles(const int _x, const int _y, std::map<std::pair<int, int>, int>& _area)
	{
		int landCount = 0;

		for (int nx = _x - 1; nx <= _x + 1; nx++) {
			for (int ny = _y - 1; ny <= _y + 1; ny++)
			{
				if (_area.count({ nx, ny })) {
					if (nx == _x && ny == _y) continue;
					landCount += _area[{nx, ny}];
				}
			}
		}
		return landCount;
	}

	void Grid::CalculateBiomes()
	{
		float allBiomesValues = 0;
		for (auto& [biomeType, fillValue] : biomesFillValues) {
			allBiomesValues += fillValue;
		}
		const float valuePercentage = 100.0f / allBiomesValues;

		float previousBiomeValue = 0;
		for (const auto& bv : biomesFillValues) {
			if (bv.second == 0) continue;

			auto bvCopy = bv;
			bvCopy.second = valuePercentage * bvCopy.second + previousBiomeValue;
			previousBiomeValue = bvCopy.second;

			biomesFillPercent.insert(bvCopy);
		}
		biomesFillPercent.rbegin()->second = 100.0f;
	}

	void Grid::GenerateBiomes()
	{
		std::random_device rd;
		std::mt19937 mt(rd());

		std::uniform_int_distribution dist(0, 99);

		for (auto [pos, island] : islandTiles) {
			const int lx = pos.first;
			const int ly = pos.second;

			if (island == 0) {
				preTiles[index(lx, ly)] = BiomeType::Sea;
			}
			else {
				const int randomPercent = dist(mt);

				for (auto& [biomeType, fillPercent] : biomesFillPercent) {
					if (randomPercent < fillPercent)
					{
						preTiles[index(lx, ly)] = biomeType;
						break;
					}
				}
			}
		}

		for (int i = 0; i < 2; i++)
		{
			SmoothBiomes();
		}

		//CreateSeaAndLakeRegions();
	}

	void Grid::SmoothBiomes()
	{
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				if (preTiles[index(x, y)] != BiomeType::None && preTiles[index(x, y)] != BiomeType::Sea)
				{
					CheckBiome(x, y);
				}
			}
		}
	}
	void Grid::CheckBiome(const int _x, const int _y)
	{
		std::map<BiomeType, float> biomeStrengths;

		for (int nx = _x - 1; nx <= _x + 1; nx++) {
			for (int ny = _y - 1; ny <= _y + 1; ny++)
			{
				if (nx >= 0 && nx < width && ny >= 0 && ny < height)
				{
					if (preTiles[index(nx, ny)] == BiomeType::None || preTiles[index(nx, ny)] == BiomeType::Sea)
						continue;

					if (nx == _x && ny == _y) {
						biomeStrengths[preTiles[index(nx, ny)]] += 2.0f;
					}
					biomeStrengths[preTiles[index(nx, ny)]] += 1.0f;
				}
			}
		}

		for (auto& [biomeType, strength] : biomeStrengths) {
			if (strength > biomeStrengths[preTiles[index(_x, _y)]]) {
				preTiles[index(_x, _y)] = biomeType;
			}
		}
	}

	void Grid::CreateSeaAndLakeRegions()
	{
		std::map<std::pair<int, int>, int> labels;

		std::map<int, int> equivalencies;

		int nextLabel = 1;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				const BiomeType tileBiome = preTiles[index(x, y)];
				if (tileBiome != BiomeType::Sea && tileBiome != BiomeType::Lake) {
					labels.insert({ {x, y}, 0 });
				}
				else {
					const BiomeType leftTileBiome = preTiles[index(x - 1, y)];
					const BiomeType aboveTileBiome = preTiles[index(x, y - 1)];

					int leftLabel = labels[{x - 1, y}];
					int aboveLabel = labels[{x, y - 1}];

					if (leftTileBiome == BiomeType::Sea || leftTileBiome == BiomeType::Lake) {
						labels.insert({ {x, y}, leftLabel });

						if (aboveTileBiome == BiomeType::Sea || aboveTileBiome == BiomeType::Lake) {
							if (leftLabel != aboveLabel)
							{
								if (leftLabel > aboveLabel) {
									labels[{x, y}] = aboveLabel;
									equivalencies[leftLabel] = aboveLabel;
								}
								else {
									labels[{x, y}] = leftLabel;
									equivalencies[aboveLabel] = leftLabel;
								}
							}
						}
					}
					else if (aboveTileBiome == BiomeType::Sea || aboveTileBiome == BiomeType::Lake) {
						labels.insert({ {x, y}, aboveLabel });
					}
					else {
						labels.insert({ {x, y}, nextLabel });
						equivalencies.insert({ nextLabel, nextLabel });
						nextLabel++;
					}
				}
			}
		}
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				int label = labels[{x, y}];
				if (label != 0) {
					while (label != equivalencies[label]) {
						label = equivalencies[label];
					}
				}
			}
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				const int label = labels[{x, y}];
				if (label == 1) {
					preTiles[index(x, y)] = BiomeType::Sea;
				}
				if (label > 1) {
					preTiles[index(x, y)] = BiomeType::Lake;
				}
			}
		}
	}

	void Grid::CreateMap()
	{
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)
			{
				CreateTile(x, y, preTiles[index(x, y)]);
			}
		}
	}

	void Grid::CreateTile(int _x, int _y, const BiomeType _biomeType)
	{
		const std::string spriteName = GetRandomElementFrom(biomeSprites.at(_biomeType));
		const std::string spritePath = GetSpritePath(spriteName);

		Tile* tile = new Tile(spritePath, {_x, _y}, _biomeType);
		// TODO / Create the resource inside GameScene

		tiles.push_back(tile);
	}
}
