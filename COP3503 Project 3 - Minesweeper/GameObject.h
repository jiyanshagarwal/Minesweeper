#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
	GameObject(int x = 0, int y = 0);

	virtual void Draw(sf::RenderWindow& window);

	void SetTexture(const sf::Texture& texture);
	void SetPosition(int x, int y);

	sf::Vector2u Size() const;
	sf::Vector2f Position() const;
	bool InBounds(int x, int y) const;

protected:
	sf::Vector2f position;
	sf::Sprite sprite;
};