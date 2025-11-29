#pragma once

#ifndef BIOMES_H
#define BIOMES_H

#include <map>
#include <string>
#include <vector>

namespace game
{
	const std::map<BiomeType, std::vector<std::string>> biomeSprites =
	{
		{ BiomeType::None, { "Tile None" } },
		{ BiomeType::Field, { "Tile Field 1", "Tile Field 2", "Tile Field 3", "Tile Field 4" } },
		{ BiomeType::Desert, { "Tile Desert 1", "Tile Desert 2", "Tile Desert 3" } },
		{ BiomeType::Mountain, { "Tile Mountain 1", "Tile Mountain 2", "Tile Mountain 3" } },
		{ BiomeType::Forest, { "Tile Forest 1 AA", "Tile Forest 2 AA", "Tile Forest 3 AA", "Tile Forest 4 AA" } },
		{ BiomeType::Lake, { "Tile Lake Center 1", "Tile Lake Center 2" } },
		{ BiomeType::Sea, { "Tile Sea 1", "Tile Sea 2", "Tile Sea 3" } },
	};
}

#endif // !BIOMES_H
