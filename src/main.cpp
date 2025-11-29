#include "GameEngine.h"

using namespace core;

int main()
{
    // Map Generation Demo

    GameEngine gameEngine = GameEngine();

    sf::RenderWindow* gameWindow = gameEngine.GetGameDisplay()->GetRenderWindow();

    gameWindow->setFramerateLimit(60);

    sf::Clock clock;

    gameEngine.Start();

    while (gameWindow->isOpen())
    {
        sf::Time elapsed = clock.restart();
        float elapsedTime = elapsed.asSeconds();

        while (const std::optional event = gameWindow->pollEvent())
        {
            if (event.type == sf::Event::Closed)
                gameWindow->close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.alt == Keyboard::F4)
                    gameWindow->close();
            }

            gameEngine.EventRun(event, elapsedTime);
        }

        gameEngine.Run(elapsedTime);
    }

    return 0;

    // State Machine AI Demo

    // Miner* Alfred = new Miner(AGENT_MINER);
    //
    // Wife* Elsa = new Wife(AGENT_WIFE);
    //
    // AgentManager::Instance()->RegisterAgent(Alfred);
    // AgentManager::Instance()->RegisterAgent(Elsa);
    //
    // for (int i = 0; i < 30; ++i)
    // {
    //     Alfred->Update();
    //     Elsa->Update();
    //
    //     MessageDispatcher::Instance()->DispatchDelayedMessages();
    //
    //     Sleep(800);
    // }
    //
    // delete Alfred;
    // delete Elsa;
    //
    // PressAnyKeyToContinue();
    //
    // return 0;

    // Default SFML Demo

    // sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    //
    // while (window.isOpen())
    // {
    //     while (const std::optional event = window.pollEvent())
    //     {
    //         if (event->is<sf::Event::Closed>())
    //             window.close();
    //     }
    //
    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }
}
