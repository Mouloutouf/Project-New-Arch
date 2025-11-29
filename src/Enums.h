#pragma once

#ifndef ENUMS_H
#define ENUMS_H

namespace game
{
	enum class BiomeType
	{
		None, Forest, Field, Desert, Mountain, Sea, Lake
	};

	enum class TerrainType
	{
		Normal, Hard
	};

	enum class ResourceType
	{
		Wood, Stone, Iron
	};
}

#endif // !ENUMS_H
