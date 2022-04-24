#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class MineCounter : public GameObject {
public:
	const static int DIGIT_WIDTH = 21;
	const static int DIGIT_HEIGHT = 32;

	MineCounter(int x = 0, int y = 0);
	void Draw(sf::RenderWindow& window) override;
	void SetCount(int count);
private:
	int count;
};