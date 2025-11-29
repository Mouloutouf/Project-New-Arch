#pragma once

#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include <map>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"

#include "GameEntity.h"

namespace core
{
	class DisplayedObject
	{
	public:
		DisplayedObject(GameEntity* _gameObject, RenderObject* _renderObject, Camera* _cam, sf::Vector2f _origin);
		~DisplayedObject();

		void CalculateDraw();
		void CalculateUIDraw();

		GameEntity* gameObjectToRender;

		RenderObject* objectToRender = nullptr;
		bool isUI;
		bool isText;

		int ppu;
		Camera* cam;

		sf::Vector2f origin;

		sf::Vector2f cachedDisplayPos; // -> World position, center of the sprite is (0, 0)
		sf::Vector2f cachedDrawPos; // -> Draw Position, top-left corner of the sprite is (0, 0), same position as above but with offset from the center to match the origin
		sf::Vector2f cachedDisplayScale;
	};

	class GameDisplay
	{
	public:
		GameDisplay();
		GameDisplay(sf::VideoMode _videoMode, const std::string& _name);
		~GameDisplay();

		void AddObjectToRender(GameEntity* _gameObject, RenderObject* _renderObject);
		void RemoveObjectToRender(RenderObject* _renderObject);

		void Clear();
		void Render();

		void Draw(const sf::Drawable* _drawable);
		void DebugDraw(DisplayedObject* _d);
		void DrawBackground();
		void DrawGrid();

		sf::Vector2f ScreenToWorldPosition(sf::Vector2f _screenPosition);
		sf::Vector2f WorldToScreenPosition(sf::Vector2f _worldPosition);
		sf::Vector2f MousePositionToWorld();

		void SetBackgroundColor(sf::Color _color);
		sf::Color BackgroundColor() const;

		Camera* camera = nullptr;

	private:
		sf::RenderWindow gameWindow;

		sf::Vector2f resolution;
		sf::Vector2f displayOrigin() const { return resolution / 2.0f; }

		std::vector<int> entries;
		std::map<int, std::vector<DisplayedObject*>> displayedObjects;

		int FindKeyPosition(int _newKey) const;

		std::pair<int, int> ContainsObjectToRender(RenderObject* _renderObject);

		sf::Vector2f worldOrigin() {
			sf::Vector2f origin = -camera->gameObject->transform->position();
			origin *= static_cast<float>(camera->pixelsPerUnit());
			origin = sf::Vector2f(displayOrigin().x + origin.x, displayOrigin().y - origin.y);
			return origin;
		}

		sf::Color backgroundColor = BACKGROUND_COLOR;
	};
}

#endif // !GAME_DISPLAY_H
