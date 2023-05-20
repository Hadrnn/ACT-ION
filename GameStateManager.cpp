#include "GameStateManager.h"

void StateManager::changeState(GameStateId id, const std::string& arg) {
	if (curr_state_) {
		delete curr_state_;
	}

	switch (id) {
	case GameStateId::MainMenu:
		curr_state_ = new MainMenuGameState;
		break;
	case GameStateId::HostMenu:
		curr_state_ = new HostMenuGameState;
		break;
	case GameStateId::ClientMenu:
		curr_state_ = new ClientMenuGameState;
		break;
	case GameStateId::HostPlaying:
		curr_state_ = new HostPlayingGameState(arg);
		break;
	case GameStateId::ClientPlaying:
		curr_state_ = new ClientPlayingGameState(arg);
		break;
	default:
		break;
	}
}

void StateManager::run(sf::RenderWindow& window) {
	GameStateId nextGameState = curr_state_->update(window);

	if (nextGameState != curr_state_->getStateId()) { ///////////////////////// �������� ����� �����
		changeState(nextGameState, std::string("Maps/lvlTest2.txt"));
	}
};
