#include <SFML/Graphics.hpp>
#include "GameManager.h"
using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper!");
	window.setFramerateLimit(60);
	GameManager game;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					game.LeftClick(event.mouseButton.x, event.mouseButton.y);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					game.RightClick(event.mouseButton.x, event.mouseButton.y);
				}
			}
		}

		window.clear();
		game.Draw(window);
		window.display();
	}
	
	return 0;
}