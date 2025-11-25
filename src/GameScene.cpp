#include "GameScene.h"

namespace core
{
    GameScene::GameScene()
    {
    }
    GameScene::GameScene(const std::string& _name)
        : name(_name)
    {
    }

    GameScene::~GameScene()
    {
        for (const auto& go : gameObjects)
            if (go != nullptr) delete go;
    }

    GameEntity* GameScene::CreateGameObject(const std::string& _name, const sf::Transformable& _transform, const Layer _layer)
    {
        gameObjects.push_back(new GameEntity(_name, _transform, _layer));
        const auto go = gameObjects.back();
        go->SetIndex(static_cast<int>(gameObjects.size()) - 1);

        if (isRunning) {
            go->Start();
        }

        return go;
    }

    GameEntity* GameScene::InstantiateGameObject(const GameEntity* _gameObject)
    {
        gameObjects.push_back(new GameEntity(*_gameObject));
        const auto go = gameObjects.back();
        go->SetIndex(static_cast<int>(gameObjects.size()) - 1);

        if (isRunning) {
            go->Start();
        }

        return go;
    }

    void GameScene::DestroyGameObject(const GameEntity* _gameObject)
    {
        gameObjects.erase(gameObjects.begin() + _gameObject->GetIndex());
        delete _gameObject;
    }

    void GameScene::Init()
    {
        UserInit();
    }

    void GameScene::UserInit()
    {
        GameEntity* cameraObject = CreateGameObject("Main Camera");
        cameraObject->AddTag(Tag::Main_Camera);
        cameraObject->AddComponent(new Camera(&currentDisplay, currentDisplay.resolution, 7));

        mainCamera = GetMainCamera();

        cameraObject->AddComponent(new CameraInput(mainCamera));

        GameEntity* gridObject = CreateGameObject("Grid");
        auto grid = gridObject->AddComponent(new Grid(48, 24));
        grid->camera = mainCamera;

        GameEntity* constructionInputObject = CreateGameObject("Construction Input");
        constructionInputObject->AddComponent(new ConstructionInput(currentDisplay, gridObject->GetComponent<Grid>()));

        auto canvasPrefab = CreateGameObject("Canvas", nullptr, new UITransform((UITransform*)nullptr));
        auto canvas = canvasPrefab->AddComponent(new Canvas(canvasPrefab, RenderSpace::ScreenSpace, &currentDisplay));
    }

    void GameScene::Start()
    {
        isRunning = true;

        for (int i = 0; i < gameObjects.size(); ++i)
            if (gameObjects[i] != nullptr) gameObjects[i]->Start();
    }

    void GameScene::Update(const float _elapsedTime) const
    {
        for (int i = 0; i < gameObjects.size(); ++i)
            if (gameObjects[i] != nullptr) gameObjects[i]->Update(_elapsedTime);
    }

    void GameScene::EventUpdate(sf::Event& _event, const float _elapsedTime) const
    {
        for (int i = 0; i < gameObjects.size(); ++i)
            if (gameObjects[i] != nullptr) gameObjects[i]->EventUpdate(_event, _elapsedTime);
    }

    GameEntity* GameScene::FindGameObjectWithName(const std::string& _name) const
    {
        for (auto& go : gameObjects) {
            if (go->GetName() == _name) {
                return go;
            }
        } return nullptr;
    }
}
