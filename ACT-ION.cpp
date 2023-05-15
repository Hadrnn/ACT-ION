﻿#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <vector>
#include "Server.h"
#include "Types.h"


int gameLoop(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput,
	ConnectionType* connection);

int main() {

	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput = new boost::lockfree::queue<int, MAX_LENGTH>;
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput = new boost::lockfree::queue<int, MAX_LENGTH>;
	boost::thread_group producer_threads;

	ConnectionType* connection_ = new ConnectionType(ConnectionType::Null);

	producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput, connection_]() { netWork(LockFreeQueueInput, LockFreeQueueOutput, connection_); });
	producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput, connection_]() { gameLoop(LockFreeQueueInput, LockFreeQueueOutput, connection_); });

	producer_threads.join_all();

	return 0;

}

int gameLoop(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput,
	ConnectionType* connection) {

	GameState* curr_state = new HostPlayingGameState();

	sf::RenderWindow window(sf::VideoMode({ 1900,1000 }), "ACT-ION");


	while (1) {
		curr_state = curr_state->update(window);
		GameStateId curr_id = curr_state->getStateId();

		if (curr_id == GameStateId::HostPlaying) {
			*connection = ConnectionType::Host;
		}
		else if ((curr_id == GameStateId::ClientPlaying)) {
			*connection = ConnectionType::Client;
		}
	}
}