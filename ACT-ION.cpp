﻿#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <vector>


int main() {

	GameState* curr_state = new ClientMenuGameState();

	sf::RenderWindow window(sf::VideoMode({ 1900,1000  }), "ACT-ION");

	while (1) {
		curr_state = curr_state->update(window);

	}
}