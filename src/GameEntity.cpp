#include "GameEntity.h"

namespace core
{
	GameEntity::GameEntity(const std::string& _name, const sf::Transformable& _transform, const Layer _layer)
		: transform(_transform), name(_name), layer(_layer)
	{
	}
	GameEntity::GameEntity(const GameEntity& that)
		: transform(that.transform), name(that.name), layer(that.layer), active(that.active)
	{
	}

	void GameEntity::SetActive(const bool _value)
	{
		active = _value;
	}

	bool GameEntity::IsActive() const
	{
		return active;
	}
}
