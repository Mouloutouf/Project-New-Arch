#include "GameEngine.h"

namespace core
{
	GameEngine::GameEngine()
		: gameDisplay(sf::VideoMode(sf::Vector2u(1920, 1080)), "Procjam Test"), gameScene("Map Generation Scene")
	{
	}

	void GameEngine::Start()
	{
		gameScene.Init();
		gameScene.Start();
	}

	void GameEngine::Run(const float _elapsedTime)
	{
		gameScene.Update(_elapsedTime);

		gameDisplay.Render();
	}

	void GameEngine::EventRun(sf::Event& _event, const float _elapsedTime) const
	{
		gameScene.EventUpdate(_event, _elapsedTime);
	}
}
