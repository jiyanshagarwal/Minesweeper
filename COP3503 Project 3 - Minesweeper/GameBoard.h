#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "Assets.h"

class GameBoard {
public:
	bool debug_show_mines;

	const static int DEFAULT_WIDTH, DEFAULT_HEIGHT;
	const static int DEFAULT_NUM_MINES;

	struct Tile {
		enum State { COVERED, UNCOVERED, FLAGGED };
		bool isAMine;
		State state;
		int num_adjacent_mines;
	};

	GameBoard(unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_HEIGHT, unsigned int num_mines = DEFAULT_NUM_MINES);
	GameBoard(const std::vector<Tile>& tiles, unsigned int width);

	void GenerateBoard(unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_HEIGHT, unsigned int num_mines = DEFAULT_NUM_MINES);
	void Reveal(int row, int col);
	bool Peek(int row, int col);
	void Hide(int row, int col);
	void ToggleFlag(int row, int col);
	void FlagAllMines();
	bool isGameOver();

	void Draw(sf::RenderWindow& window, const Assets& assets);

	int Width() const;
	int Height() const;
	int MineCount() const;
	int FlagCount() const;
	int RevealedCount() const;
	bool MineClicked() const;
	const std::vector<Tile>& Tiles() const;
	bool InBounds(int row, int col) const;

private:
	int width, height;
	int num_mines;
	std::vector<Tile> tiles;
	bool mine_clicked;

	int flag_count;
	int reveal_count;

	static std::mt19937 random_mt;

	std::vector<bool> RandomizeBoard();
	void CalculateAdjacentMines(int row, int col);
};