#pragma once

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <string>

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Event.hpp"

namespace core
{
	enum class Layer { Default };

	class GameEntity
	{
	public:
		GameEntity(const std::string& _name = "New Game Object", const sf::Transformable& _transform = sf::Transformable(), Layer _layer = Layer::Default);
		GameEntity(const GameEntity& that);
		virtual ~GameEntity() = default;

		virtual void Start() = 0;
		virtual void Update(float _elapsedTime) = 0;
		virtual void EventUpdate(sf::Event& _event, float _elapsedTime) = 0;

		void SetActive(bool _value);
		bool IsActive() const;

		sf::Transformable* GetTransform() { return &transform; }

		std::string GetName() { return name; }
		void SetName(const std::string& _name) { name = _name; }

		Layer GetLayer() const { return layer; }

		int GetIndex() const { return index; }
		void SetIndex(const int _value) { index = _value; }

	private:
		sf::Transformable transform;

		std::string name;
		Layer layer;

		int index = 0;

		bool active = true;
	};
}

#endif // !GAME_ENTITY_H
