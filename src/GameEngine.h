#pragma once

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "GameDisplay.h"
#include "GameScene.h"

namespace core
{
	class GameScene;
	class GameDisplay;

	class GameEngine
	{
	public:
		GameEngine();

		void Start();
		void Run(float _elapsedTime);
		void EventRun(sf::Event& _event, float _elapsedTime) const;

		GameDisplay* GetGameDisplay() { return &gameDisplay; }
		GameScene* GetGameScene() { return &gameScene; }

	protected:
		GameDisplay gameDisplay;
		GameScene gameScene;
	};
}

#endif // !GAME_ENGINE_H
