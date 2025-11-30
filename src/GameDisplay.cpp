#include "GameDisplay.h"

#include <cmath>
#include <iostream>

#include "SFML/Graphics/RectangleShape.hpp"

#include "Colors.h"

namespace core
{
	/// Displayed Object
	///
#pragma region DisplayedObject
	DisplayedObject::DisplayedObject(GameEntity* _gameObject, SpriteObject* _renderObject, Camera* _cam, const sf::Vector2f _origin)
		: gameObjectToRender(_gameObject), objectToRender(_renderObject), ppu(_renderObject->ppu), cam(_cam), origin(_origin)
	{
	}

	DisplayedObject::~DisplayedObject()
	{
	}

	void DisplayedObject::CalculateDraw()
	{
		/// Position
		sf::Vector2f pos = gameObjectToRender->GetTransform()->getPosition() - cam->gameObject->transform->position(); // Calculate the position of the displayed object relative to the camera
		pos *= static_cast<float>(cam->pixelsPerUnit()); // Convert the position from units to pixels
		pos = sf::Vector2f(origin.x + pos.x, origin.y - pos.y); // Calculate the position relative to the origin (center) of the display (and not the top left corner)

		cachedDisplayPos = pos;

		/// Scale
		sf::Vector2f scale = gameObjectToRender->GetTransform()->getScale() * (static_cast<float>(cam->pixelsPerUnit()) / static_cast<float>(ppu)); // Calculate the scale of the displayed object using the ratio
																									 // between the camera's ppu and the displayed object's ppu
		cachedDisplayScale = scale;

		/// Apply

		// Calculate the final position relative to the center of the sprite
		pos -= sf::Vector2f(objectToRender->sprite.getTextureRect().width * scale.x, objectToRender->sprite.getTextureRect().height * scale.y) / 2.0f;

		cachedDrawPos = pos;

		objectToRender->sprite.setPosition(pos);
		objectToRender->sprite.setScale(scale);
	}
#pragma endregion
	///

	/// Display
	///
#pragma region Display
	GameDisplay::GameDisplay()
	{
	}

	GameDisplay::GameDisplay(const sf::VideoMode _videoMode, const std::string& _name)
		: gameWindow(sf::RenderWindow(_videoMode, _name)), resolution(gameWindow.getSize())
	{
	}

	GameDisplay::~GameDisplay()
	{
		for (auto& [first, second] : displayedObjects) {
			for (const auto& d : second)
				delete d;
		}
	}

#pragma region Setup

	void GameDisplay::AddObjectToRender(GameEntity* _gameObject, SpriteObject* _renderObject)
	{
		if (ContainsObjectToRender(_renderObject).first >= 0) return;

		int layer = _renderObject->layer + _renderObject->orderInLayer;

		if (!displayedObjects.count(layer)) {
			int k = FindKeyPosition(layer);
			entries.insert(entries.begin() + k, layer);
			displayedObjects.insert({ layer, std::vector<DisplayedObject*>() });
		}
		const auto d = new DisplayedObject(_gameObject, _renderObject, camera, displayOrigin());
		displayedObjects[layer].push_back(d);
	}
	int GameDisplay::FindKeyPosition(const int _newKey) const
	{
		for (int i = 0; i < entries.size(); i++)
		{
			if (entries[i] > _newKey) {
				return i;
			}
		}
		return -1;
	}

	void GameDisplay::RemoveObjectToRender(const SpriteObject* _renderObject)
	{
		if (auto [layer, index] = ContainsObjectToRender(_renderObject); layer >= 0)
		{
			delete displayedObjects[layer][index];
			displayedObjects[layer].erase(displayedObjects[layer].begin() + index);
		}
	}

	std::pair<int, int> GameDisplay::ContainsObjectToRender(const SpriteObject* _renderObject)
	{
		for (auto& [layer, displayedObjectsInLayer] : displayedObjects) {
			for (int i = 0; i < displayedObjectsInLayer.size(); ++i) {
				if (displayedObjectsInLayer[i]->objectToRender == _renderObject)
					return { layer, i };
			}
		} return { -1, -1 };
	}
#pragma endregion

	void GameDisplay::Clear()
	{
		gameWindow.clear();
	}

	void GameDisplay::Render()
	{
		DrawBackground();
		//DrawGrid();

		for (int i = 0; i < entries.size(); i++) {
			for (const auto& d : displayedObjects[entries[i]])
			{
				if (d->objectToRender->render == false)
					continue;

				d->CalculateDraw();

				for (const auto& dw : d->objectToRender->drawables)
					Draw(dw);
			}
		}

		//RectangleShape rect = RectangleShape(Vector2f(1, 1));
		//rect.setFillColor(Color::Blue);
		//rect.setSize(Vector2f(400, 100));
		//rect.setOutlineThickness(-1.0f);
		//gameWindow->window->draw(rect);

		gameWindow.display();
	}

	void GameDisplay::Draw(const sf::Drawable* _drawable)
	{
		gameWindow.draw(*_drawable);
	}

	void GameDisplay::DebugDraw(const DisplayedObject* _d)
	{
		auto point = sf::RectangleShape(sf::Vector2f(4, 4));
		point.setFillColor(RED_COLOR);
		point.setPosition(_d->cachedDisplayPos);
		gameWindow.draw(point);

		const auto spriteToRender = _d->objectToRender;

		auto rect = sf::RectangleShape(sf::Vector2f(
			spriteToRender->sprite.getTextureRect().size.x * _d->cachedDisplayScale.x,
			spriteToRender->sprite.getTextureRect().size.y * _d->cachedDisplayScale.y));
		rect.setOutlineColor(GREEN_COLOR);
		rect.setOutlineThickness(1);
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setPosition(_d->cachedDrawPos);
		gameWindow.draw(rect);
	}

	void GameDisplay::DrawBackground()
	{
		auto rect = sf::RectangleShape(sf::Vector2f(resolution.x, resolution.y));
		rect.setFillColor(backgroundColor);
		gameWindow.draw(rect);
	}

	void GameDisplay::DrawGrid()
	{
		int camPPU = camera->pixelsPerUnit();

		constexpr int step = 1000;

		/// Camera Dimensions
		sf::Vector2f camPosition = camera->gameObject->transform->position();
		sf::Vector2f cachedCamOffset = sf::Vector2f(resolution.x / 2 / camPPU, resolution.y / 2 / camPPU);
		sf::Vector2f minCamPos = camPosition - cachedCamOffset;
		sf::Vector2f maxCamPos = camPosition + cachedCamOffset;

		int lineCount = static_cast<int>(floor(maxCamPos.x) - ceil(minCamPos.x));

		int power = Utility::powerOf(static_cast<float>(lineCount) / 2, step);
		int base = static_cast<int>(pow(step, power));
		int currentPPU = camPPU * base;

		int linesX = static_cast<int>(Utility::pfloor(maxCamPos.x, base) / base - Utility::pceil(minCamPos.x, base) / base);
		std::cout << linesX << std::endl;

		float xPos = Utility::pceil(minCamPos.x, base);
		xPos -= camPosition.x;
		xPos *= camPPU;
		xPos += displayOrigin().x;

		for (int x = 0; x <= linesX; ++x)
		{
			float pos = xPos + static_cast<float>(x * currentPPU);
			sf::Vertex line[] = {sf::Vertex(sf::Vector2f(pos, 0)), sf::Vertex(sf::Vector2f(pos, resolution.y)) };
			line->color = DETAIL_COLOR;
			//line->color.a =
			gameWindow.draw(line, 2, sf::PrimitiveType::Lines);
		}

		float yPos = Utility::pceil(minCamPos.y, base);
		yPos -= camPosition.y;
		yPos *= camPPU;
		yPos += displayOrigin().y;

		int linesY = static_cast<int>(Utility::pfloor(maxCamPos.y, base) / base - Utility::pceil(minCamPos.y, base) / base);

		for (int y = 0; y <= linesY; ++y)
		{
			float pos = yPos + static_cast<float>(y * currentPPU);
			sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0, pos)), sf::Vertex(sf::Vector2f(resolution.x, pos)) };
			line->color = DETAIL_COLOR;
			gameWindow.draw(line, 2, sf::PrimitiveType::Lines);
		}

		auto rect = sf::RectangleShape(sf::Vector2f(15, 15));
		rect.setOutlineColor(RED_COLOR);
		rect.setOutlineThickness(1);
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setPosition(sf::Vector2f(worldOrigin().x - rect.getSize().x / 2, worldOrigin().y - rect.getSize().y / 2));
		gameWindow.draw(rect);
	}
#pragma endregion

	sf::Vector2f GameDisplay::ScreenToWorldPosition(sf::Vector2f _screenPosition)
	{
		_screenPosition = sf::Vector2f(_screenPosition.x - displayOrigin().x, displayOrigin().y - _screenPosition.y);
		_screenPosition /= static_cast<float>(camera->pixelsPerUnit());
		_screenPosition += camera->gameObject->transform->position();
		return _screenPosition;
	}
	sf::Vector2f GameDisplay::WorldToScreenPosition(sf::Vector2f _worldPosition)
	{
		_worldPosition -= camera->gameObject->transform->position();
		_worldPosition *= static_cast<float>(camera->pixelsPerUnit());
		_worldPosition = sf::Vector2f(displayOrigin().x + _worldPosition.x, displayOrigin().y - _worldPosition.y);
		return _worldPosition;
	}

	sf::Vector2f GameDisplay::MousePositionToWorld()
	{
		const auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(gameWindow));
		return ScreenToWorldPosition(mousePosition);
	}

	void GameDisplay::SetBackgroundColor(const sf::Color _color) { backgroundColor = _color; }

	sf::Color GameDisplay::BackgroundColor() const { return backgroundColor; }
}
