#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "GameBoard.h"
#include "Assets.h"
#include "GameObject.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	void Initalize();
	void Draw(sf::RenderWindow& window);
	void CheckGameOver();

	void LeftClick(int x, int y);
	void RightClick(int x, int y);

private:
	std::unordered_map<std::string, GameObject*> objects;
	GameBoard board;
	Assets assets;
	int tile_size;

	void Delete();
};