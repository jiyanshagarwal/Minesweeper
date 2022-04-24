#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <stdexcept>
#include <ctime>
#include "GameBoard.h"
#include "Assets.h"

const int GameBoard::DEFAULT_WIDTH = 25;
const int GameBoard::DEFAULT_HEIGHT = 16;
const int GameBoard::DEFAULT_NUM_MINES = 50;

std::mt19937 GameBoard::random_mt = std::mt19937((unsigned int)std::time(0));

GameBoard::GameBoard(unsigned int width, unsigned int height, unsigned int num_mines) {
	GenerateBoard(width, height, num_mines);
	mine_clicked = false;
	flag_count = 0;
	reveal_count = 0;
	debug_show_mines = false;
}

GameBoard::GameBoard(const std::vector<Tile>& tiles, unsigned int width) {
	if (width > tiles.size()) {
		throw std::invalid_argument("At GameBoard Constructor: Width is longer than vector<Tile> tiles size.");
	}

	this->width = width;
	this->height = 0;
	this->num_mines = 0;
	this->tiles.resize(tiles.size());
	this->mine_clicked = false;
	this->debug_show_mines = false;
	this->flag_count = 0;
	this->reveal_count = 0;

	if (width != 0) {
		this->height = tiles.size() / width;

		for (unsigned int i = 0; i < tiles.size(); i++) {
			this->tiles[i] = tiles[i];
			num_mines += tiles[i].isAMine;
		}
	}
}

void GameBoard::GenerateBoard(unsigned int width, unsigned int height, unsigned int num_mines) {
	if (num_mines > width* height) {
		throw std::invalid_argument("At GenerateBoard: num_mines greater than number of tiles (width * height)");
	}
	this->width = width;
	this->height = height;
	this->num_mines = num_mines;
	this->tiles.resize(width * height);
	this->mine_clicked = false;
	this->flag_count = 0;
	this->reveal_count = 0;

	std::vector<bool> mine_pos = RandomizeBoard();

	for (unsigned int i = 0; i < tiles.size(); i++) {
		Tile tile;
		tile.isAMine = mine_pos[i];
		tile.state = Tile::State::COVERED;
		tile.num_adjacent_mines = 0;
		tiles[i] = tile;
	}
}

void GameBoard::Reveal(int row, int col) {
	if (!isGameOver()) {
		if (!InBounds(row, col)) {
			throw std::invalid_argument("At Reveal: Row or column out of bounds.");
		}

		Tile& tile = tiles[row * width + col];

		if (tile.state == Tile::State::UNCOVERED || tile.state == Tile::State::FLAGGED) {
			return;
		}

		if (tile.isAMine) {
			mine_clicked = true;
		}
		else {
			tile.state = Tile::State::UNCOVERED;
			CalculateAdjacentMines(row, col);
			reveal_count++;

			//Recursively reveals all adjacent tiles if no adjacent mines.
			if (tile.num_adjacent_mines == 0) {
				for (int i = row - 1; i <= row + 1; i++) {
					for (int j = col - 1; j <= col + 1; j++) {
						if (i >= 0 && j >= 0 && i < height && j < width) {
							Reveal(i, j);
						}
					}
				}
			}
		}
	}
}

bool GameBoard::Peek(int row, int col) {
	if (!InBounds(row, col)) {
		throw std::invalid_argument("At Peek: Row or column out of bounds.");
	}

	Tile& tile = tiles[row * width + col];

	if (tile.isAMine == false) {
		CalculateAdjacentMines(row, col);
	}

	return tile.isAMine;
}

void GameBoard::Hide(int row, int col) {
	if (!InBounds(row, col)) {
		throw std::invalid_argument("At Hide: Row or column out of bounds.");
	}

	tiles[row * width + col].state = Tile::State::COVERED;
}

void GameBoard::ToggleFlag(int row, int col) {
	if (!isGameOver()) {
		if (!InBounds(row, col)) {
			throw std::invalid_argument("At Flag: Row or column out of bounds.");
		}

		Tile& tile = tiles[row * width + col];

		if (tile.state == Tile::State::UNCOVERED) {
			return;
		}
		else if (tile.state == Tile::State::FLAGGED) {
			flag_count--;
			tile.state = Tile::State::COVERED;
		}
		else {
			flag_count++;
			tile.state = Tile::State::FLAGGED;
		}
	}
}

void GameBoard::FlagAllMines() {
	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles[i].isAMine) {
			tiles[i].state = Tile::State::FLAGGED;
		}
	}
	flag_count = num_mines;
}

bool GameBoard::isGameOver() {
	if (mine_clicked) {
		return true;
	}
	if (reveal_count == tiles.size() - num_mines) {
		return true;
	}
	return false;
}

void GameBoard::Draw(sf::RenderWindow& window, const Assets& assets) {
	sf::Sprite sprite_bottom, sprite_top;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			Tile& tile = tiles[row * width + col];

			if (tile.state == Tile::State::COVERED) {
				sprite_bottom.setTexture(assets.hidden_tile);
				sprite_top.setTexture(assets.hidden_tile);
			}
			else if (tile.state == Tile::State::FLAGGED) {
				sprite_bottom.setTexture(assets.hidden_tile);
				sprite_top.setTexture(assets.flag);
			}
			else {
				sprite_bottom.setTexture(assets.revealed_tile);

				if (tile.isAMine) {
					sprite_top.setTexture(assets.mine);
				}
				else {
					switch (tile.num_adjacent_mines) {
					case 0:
						sprite_top.setTexture(assets.revealed_tile);
						break;
					case 1:
						sprite_top.setTexture(assets.num_1);
						break;
					case 2:
						sprite_top.setTexture(assets.num_2);
						break;
					case 3:
						sprite_top.setTexture(assets.num_3);
						break;
					case 4:
						sprite_top.setTexture(assets.num_4);
						break;
					case 5:
						sprite_top.setTexture(assets.num_5);
						break;
					case 6:
						sprite_top.setTexture(assets.num_6);
						break;
					case 7:
						sprite_top.setTexture(assets.num_7);
						break;
					case 8:
						sprite_top.setTexture(assets.num_8);
						break;
					default:
						sprite_top.setTexture(assets.revealed_tile);
					}
				}
			}

			if (mine_clicked && tile.isAMine) {
				sprite_bottom.setTexture(assets.revealed_tile);
				sprite_top.setTexture(assets.mine);
			}

			sf::Vector2f tile_size(assets.hidden_tile.getSize());
			sprite_bottom.setPosition(sf::Vector2f(tile_size.x * col, tile_size.y * row));
			sprite_top.setPosition(sf::Vector2f(tile_size.x * col, tile_size.y * row));
			window.draw(sprite_bottom);
			window.draw(sprite_top);

			if (debug_show_mines && tile.isAMine) {
				sprite_top.setTexture(assets.mine);
				window.draw(sprite_top);
			}
		}
	}
}

int GameBoard::Width() const { return width; }
int GameBoard::Height() const { return height; }
int GameBoard::MineCount() const { return num_mines; }
int GameBoard::FlagCount() const { return flag_count; }
int GameBoard::RevealedCount() const { return reveal_count; }
bool GameBoard::MineClicked() const { return mine_clicked; }
const std::vector<GameBoard::Tile>& GameBoard::Tiles() const { return tiles; }

bool GameBoard::InBounds(int row, int col) const {
	return (row >= 0 && col >= 0 && row < height && col < width);
}

std::vector<bool> GameBoard::RandomizeBoard() {
	std::vector<bool> board(width * height);
	std::uniform_int_distribution<int> distribution(0, width * height - 1);

	for (int i = 0; i < num_mines; i++) {
		int index = distribution(random_mt);

		//This is to prevent the same tile from being set to true twice and thus, there wouldn't be num_mines mines.
		if (board[index] == true) {
			i--;
		}

		board[index] = true;
	}

	return board;
}

void GameBoard::CalculateAdjacentMines(int row, int col) {
	if (!InBounds(row, col)) {
		throw std::invalid_argument("At CalculateAdjacentMines: Row or column out of bounds.");
	}

	Tile& tile = tiles[row * width + col];

	//If num_adjacent_mines is not 0, they have already been calculated
	if (tile.num_adjacent_mines != 0) {
		return;
	}

	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			if (i >= 0 && j >= 0 && i < height && j < width) {
				tile.num_adjacent_mines += tiles[i * width + j].isAMine;

			}
		}
	}
}