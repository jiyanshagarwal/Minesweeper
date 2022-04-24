#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameManager.h"
#include "GameObject.h"
#include "MineCounter.h"
#include "GameBoardFileIO.h"

GameManager::GameManager() {
	board.GenerateBoard();
	Initalize();
}

GameManager::~GameManager() {
	Delete();
}

void GameManager::Initalize() {
	Delete();

	tile_size = assets.hidden_tile.getSize().y;
	int object_y = tile_size * board.Height();
	int button_width = assets.debug.getSize().x;

	GameObject* mine_counter = new MineCounter(0, object_y);
	mine_counter->SetTexture(assets.digits);

	GameObject* face_button = new GameObject(368, object_y);
	face_button->SetTexture(assets.happy_face);

	GameObject* debug_button = new GameObject(496, object_y);
	debug_button->SetTexture(assets.debug);

	GameObject* test1_button = new GameObject((int)(debug_button->Position().x + button_width * 1), object_y);
	test1_button->SetTexture(assets.test_1);

	GameObject* test2_button = new GameObject((int)(debug_button->Position().x + button_width * 2), object_y);
	test2_button->SetTexture(assets.test_2);

	GameObject* test3_button = new GameObject((int)(debug_button->Position().x + button_width * 3), object_y);
	test3_button->SetTexture(assets.test_3);

	objects.emplace("mine_counter", mine_counter);
	objects.emplace("face_button", face_button);
	objects.emplace("debug_button", debug_button);
	objects.emplace("test1_button", test1_button);
	objects.emplace("test2_button", test2_button);
	objects.emplace("test3_button", test3_button);
}

void GameManager::Draw(sf::RenderWindow& window) {
	CheckGameOver();
	((MineCounter*)(objects["mine_counter"]))->SetCount(board.MineCount() - board.FlagCount());
	board.Draw(window, assets);

	for (auto iter = objects.begin(); iter != objects.end(); iter++) {
		iter->second->Draw(window);
	}
}

void GameManager::CheckGameOver() {
	if (board.isGameOver()) {
		if (board.MineClicked()) {
			objects["face_button"]->SetTexture(assets.lose_face);
		}
		else {
			board.FlagAllMines();
			objects["face_button"]->SetTexture(assets.win_face);
		}
	}
	else {
		objects["face_button"]->SetTexture(assets.happy_face);
	}
}

void GameManager::LeftClick(int x, int y) {
	int row = y / tile_size;
	int col = x / tile_size;

	if (board.InBounds(row, col)) {
		board.Reveal(row, col);
	}
	else if (objects["face_button"]->InBounds(x, y)) {
		board.GenerateBoard();
		Initalize();
	}
	else if (objects["debug_button"]->InBounds(x, y)) {
		board.debug_show_mines = !board.debug_show_mines;
	}
	else if (objects["test1_button"]->InBounds(x, y)) {
		bool prev_debug_state = board.debug_show_mines;
		board = ReadBoard("boards/testboard1.brd");
		board.debug_show_mines = prev_debug_state;
		Initalize();
	}
	else if (objects["test2_button"]->InBounds(x, y)) {
		bool prev_debug_state = board.debug_show_mines;
		board = ReadBoard("boards/testboard2.brd");
		board.debug_show_mines = prev_debug_state;
		Initalize();
	}
	else if (objects["test3_button"]->InBounds(x, y)) {
		bool prev_debug_state = board.debug_show_mines;
		board = ReadBoard("boards/testboard3.brd");
		board.debug_show_mines = prev_debug_state;
		Initalize();
	}
}

void GameManager::RightClick(int x, int y) {
	int row = y / tile_size;
	int col = x / tile_size;

	if (board.InBounds(row, col)) {
		board.ToggleFlag(row, col);
	}
}

void GameManager::Delete() {
	for (auto iter = objects.begin(); iter != objects.end(); iter++) {
		delete (iter->second);
	}
	objects.clear();
}