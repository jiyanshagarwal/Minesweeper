#include <SFML/Graphics.hpp>
#include "MineCounter.h"

MineCounter::MineCounter(int x, int y) : GameObject(x, y) {
	count = 0;
}

void MineCounter::Draw(sf::RenderWindow& window) {
	int abs_count = count;

	if (count < 0) {
		sprite.setTextureRect(sf::IntRect(DIGIT_WIDTH * 10, 0, DIGIT_WIDTH, DIGIT_HEIGHT));
		abs_count = -abs_count;
	}
	else {
		sprite.setTextureRect(sf::IntRect(DIGIT_WIDTH * 0, 0, DIGIT_WIDTH, DIGIT_HEIGHT));
	}

	sf::Vector2f original_position = position;
	window.draw(sprite);

	SetPosition(DIGIT_WIDTH, (int)original_position.y);
	sprite.setTextureRect(sf::IntRect(DIGIT_WIDTH * (abs_count / 100), 0, DIGIT_WIDTH, DIGIT_HEIGHT));
	window.draw(sprite);

	SetPosition(DIGIT_WIDTH * 2, (int)original_position.y);
	sprite.setTextureRect(sf::IntRect(DIGIT_WIDTH * ((abs_count % 100) / 10), 0, DIGIT_WIDTH, DIGIT_HEIGHT));
	window.draw(sprite);

	SetPosition(DIGIT_WIDTH * 3, (int)original_position.y);
	sprite.setTextureRect(sf::IntRect(DIGIT_WIDTH * (abs_count % 10), 0, DIGIT_WIDTH, DIGIT_HEIGHT));
	window.draw(sprite);

	SetPosition((int)original_position.x, (int)original_position.y);
}

void MineCounter::SetCount(int count) {
	this->count = count;
}