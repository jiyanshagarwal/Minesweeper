#include <fstream>
#include <vector>
#include "GameBoard.h"

GameBoard ReadBoard(const char* file_name) {
	std::ifstream file(file_name);
	std::vector<GameBoard::Tile> tiles;
	int width = 0;

	if (file.is_open()) {
		std::string line;
		while (file >> line) {
			for (unsigned int i = 0; i < line.size(); i++) {
				GameBoard::Tile tile;
				tile.isAMine = line[i] == '1';
				tile.state = GameBoard::Tile::State::COVERED;
				tile.num_adjacent_mines = 0;
				tiles.push_back(tile);
			}
		}
		width = line.size();
	}

	return GameBoard(tiles, width);
}

void WriteBoard(const GameBoard& board, const char* file_name) {
	std::ofstream file(file_name);
	std::vector<GameBoard::Tile> tiles = board.Tiles();

	if (file.is_open()) {
		for (int row = 0; row < board.Height(); row++) {
			for (int col = 0; col < board.Width(); col++) {
				file << tiles[row * board.Width() + col].isAMine;
			}

			if (row < board.Height() - 1) {
				file << '\n';
			};
		}
	}
}