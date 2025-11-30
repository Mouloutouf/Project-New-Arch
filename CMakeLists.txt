cmake_minimum_required(VERSION 3.28)
project(NewArch LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/Alpha.h
        src/Enums.h
        src/Grid.h
        src/Grid.cpp
        src/Biomes.h
        src/Tile.h
        src/Tile.cpp
        src/AI/AgentState.h
        src/AI/Agent.cpp
        src/AI/Agent.h
        src/AI/Miner.cpp
        src/AI/Miner.h
        src/AI/StateMachine.h
        src/Messaging/MessageDispatcher.cpp
        src/Messaging/MessageDispatcher.h
        src/Messaging/Telegram.h
        src/AI/Locations.h
        src/AI/MinerStates.cpp
        src/AI/MinerStates.h
        src/AI/AgentManager.cpp
        src/AI/AgentManager.h
        src/Messaging/Messages.h
        src/AI/AgentNames.h
        src/AI/Wife.cpp
        src/AI/Wife.h
        src/AI/WifeStates.cpp
        src/AI/WifeStates.h
        src/GameEngine.h
        src/GameEngine.cpp
        src/GameEntity.h
        src/GameEntity.cpp
        src/GameScene.h
        src/GameScene.cpp
        src/GameDisplay.cpp
        src/GameDisplay.cpp
        src/Utility.h
        src/Utility.h
        src/SpriteObject.cpp
        src/SpriteObject.h
        src/SpriteObject.h
        src/SpriteObject.cpp
        src/Layers.h
        src/Layers.h
        src/Colors.h
        src/Colors.h
        src/Random.h
        src/Random.h)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
