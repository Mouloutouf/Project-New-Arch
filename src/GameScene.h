#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "GameEntity.h"

namespace core
{
	class GameScene
	{
	public:
		GameScene();
		GameScene(const std::string& _name = "New Scene");
		~GameScene();

		GameEntity* CreateGameObject(const std::string& _name = "New Game Object", const sf::Transformable& _transform = sf::Transformable(), Layer _layer = Layer::Default);
		GameEntity* InstantiateGameObject(const GameEntity* _gameObject);
		void DestroyGameObject(const GameEntity* _gameObject);

		GameEntity* FindGameObjectWithName(const std::string& _name) const;

		void Init();
		void UserInit();

		void Start();

		void Update(float _elapsedTime) const;
		void EventUpdate(sf::Event& _event, float _elapsedTime) const;

	private:
		std::string name;

		bool isRunning = false;

		std::vector<GameEntity*> gameObjects;
	};
}

#endif // !SCENE_H
