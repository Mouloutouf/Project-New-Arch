#pragma once

#ifndef BIOME_H
#define BIOME_H

#include "Alpha.h"

#include <map>
#include <string>
#include <vector>

#include "Enums.h"

namespace game
{
	struct Terrain
	{
		float constructionSpeed;
		float excavationSpeed;
		int buildCost;
	};

	const Terrain NORMAL_TERRAIN = Terrain{ 1, 1, 1 };
	const Terrain HARD_TERRAIN = Terrain{ 0.5f, 0.5f, 2 };

	class Biome
	{
	public:
		Biome();
		Biome(std::vector<Resource> _heldResources, std::vector<Structure> _structures);
		~Biome();

		int ExploitResource(__ResourceType _resourceType);
		void SetResource(__ResourceType _resourceType, unsigned int _amount);
		void DestroyResource(__ResourceType _resourceType);
		void DestroyResources();

		bool HasStructures();
		void AddStructure(Structure _structure);
		void RemoveStructure(StructureType _structureType);
		void RemoveAllStructures();

		void GenerateResources(__ResourceType _resourceType, int min, int max);

		BiomeType biomeType = BiomeType::None;

		std::vector<std::string> sprites;
		std::vector<std::string> spritesWithStructures;

		std::map<BuildingType, std::vector<__ResourceType>> resourcesBuildingsCanExploit;
		std::map<__ResourceType, std::string> resourceIcons;

		bool allowBuild = true;
		Terrain terrain = NORMAL_TERRAIN;

		std::map<__ResourceType, Resource> exploitationResources;

		std::map<StructureType, Structure> structures;
	};
}

#endif // !BIOME_H
