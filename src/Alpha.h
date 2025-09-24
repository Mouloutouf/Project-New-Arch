#pragma once

#ifndef ALPHA_H
#define ALPHA_H

#include <string>
#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

namespace alpha { namespace core {} namespace game {} }

#endif // !ALPHA_H

// Missing Elements
//
// Resource
// Structure
// Building
//
// GameObject
// SpriteRenderer

// New Architecture
//
// core::GameEntity => base class with a transform
//      core::VisualGameEntity => child class with a sprite renderer
//              game::Biome => represents a biome tile with its associated sprite
//      game::Grid<T as GameEntity> => child class that handles the creation and management of a tile map
//              game::Environment<Biome> => represents the environment generated procedurally