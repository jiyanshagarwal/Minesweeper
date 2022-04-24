#include "Assets.h"

Assets::Assets() {
	debug.loadFromFile("images/debug.png");
	digits.loadFromFile("images/digits.png");
	happy_face.loadFromFile("images/face_happy.png");
	lose_face.loadFromFile("images/face_lose.png");
	win_face.loadFromFile("images/face_win.png");
	flag.loadFromFile("images/flag.png");
	mine.loadFromFile("images/mine.png");
	num_1.loadFromFile("images/number_1.png");
	num_2.loadFromFile("images/number_2.png");
	num_3.loadFromFile("images/number_3.png");
	num_4.loadFromFile("images/number_4.png");
	num_5.loadFromFile("images/number_5.png");
	num_6.loadFromFile("images/number_6.png");
	num_7.loadFromFile("images/number_7.png");
	num_8.loadFromFile("images/number_8.png");
	test_1.loadFromFile("images/test_1.png");
	test_2.loadFromFile("images/test_2.png");
	test_3.loadFromFile("images/test_3.png");
	hidden_tile.loadFromFile("images/tile_hidden.png");
	revealed_tile.loadFromFile("images/tile_revealed.png");
}