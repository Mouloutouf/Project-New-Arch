#pragma once

#ifndef TILE_OBJECT_H
#define TILE_OBJECT_H

#include "Core.h"

///\

#include <map>

#include "Tile.h"

namespace alpha
{
	namespace game
	{
		class TileObject : public ScriptBehaviour
		{
		public:
			TileObject();
			TileObject(Tile* _tile, SpriteRenderer* _spriteRenderer);
			TileObject(const TileObject& that, GameObject* _gameObject);
			~TileObject();

			TileObject* Clone(GameObject* _gameObject) override;

			void Init() override;
			void Start() override;
			void Update(float _elapsedTime) override;

			void SetupTile(int x, int y);

			Tile* tile;
			Biome* biome;

			SpriteRenderer* biomeDisplay;

			GameObject* tileDisplayPrefab = nullptr;
			GameObject* tileDisplay = nullptr;

			SpriteRenderer* areaSquare = nullptr;
			SpriteRenderer* excavationIcon = nullptr;

			std::map<__ResourceType, SpriteRenderer*> resourceIconsSpriteRenderers;
		};
	}
}

#endif // !TILE_OBJECT_H
