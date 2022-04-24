#include <SFML/Graphics.hpp>
#include "GameObject.h"

GameObject::GameObject(int x, int y) {
	SetPosition(x, y);
}

void GameObject::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void GameObject::SetTexture(const sf::Texture& texture) {
	sprite.setTexture(texture);
}

void GameObject::SetPosition(int x, int y) {
	position = sf::Vector2f((float)x, (float)y);
	sprite.setPosition(position);
}

sf::Vector2u GameObject::Size() const {
	return sprite.getTexture()->getSize();
}

sf::Vector2f GameObject::Position() const {
	return position;
}

bool GameObject::InBounds(int x, int y) const {
	return sprite.getGlobalBounds().contains((float)x, (float)y);
}