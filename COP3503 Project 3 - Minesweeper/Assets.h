#pragma once
#include <SFML/Graphics.hpp>

struct Assets {
	sf::Texture debug;
	sf::Texture digits;
	sf::Texture happy_face, lose_face, win_face;
	sf::Texture flag;
	sf::Texture mine;
	sf::Texture num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8;
	sf::Texture test_1, test_2, test_3;
	sf::Texture hidden_tile, revealed_tile;

	Assets();
};