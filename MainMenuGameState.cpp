#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"
#include "GraphicsSystem.h"
#include "ButtonID.h"

// on enter()<- �������� ���� �������� �� ����� 

MainMenuGameState::MainMenuGameState() {

	id_ = GameStateId::MainMenu;
	/// ����� ������� ����������� ��� 
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;


	//����� ���� �������� ����
	Position banner_pos;
	banner_pos.x = 0;
	banner_pos.y = 0;

	Entity* banner_ent = nullptr;

	banner_ent = banner_spawner.Spawn(banner_pos, 'm');//// ��� ���? ������ ���������� ���������
	banner_ent->setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::MenuSystemId);

	//����� ������ host game �������� ����
	Position host_game_pos;
	host_game_pos.x = 200;  //��� ������������ ���� ������ � ����������� �� ������� ������
	host_game_pos.y = 800;

	Entity* host_game_ent;

	host_game_ent = button_spawner.Spawn(host_game_pos,host_game);
	host_game_ent->setEntityID(1);

	scene_.push_back(host_game_ent);

	//����� ������ connect to game �������� ����
	Position connect_game_pos;
	connect_game_pos.x = 1400;  //��� ������������ ���� ������ � ����������� �� ������� ������
	connect_game_pos.y = 800;

	Entity* connect_game_ent;

	connect_game_ent = button_spawner.Spawn(connect_game_pos, client_game);
	connect_game_ent->setEntityID(1);

	scene_.push_back(connect_game_ent);

	// ����� ������ ��������� ����
	Position single_game_button_pos;
	single_game_button_pos.x = 800;  //��� ������������ ���� ������ � ����������� �� ������� ������
	single_game_button_pos.y = 500;

	Entity* single_game_button_ent;

	single_game_button_ent = button_spawner.Spawn(single_game_button_pos, single_game);
	single_game_button_ent->setEntityID(1);

	scene_.push_back(single_game_button_ent);
}

GameStateId MainMenuGameState::update(sf::RenderWindow& window) {

	Input input;
	input.handleInput(window);
	// ���� � ���� � ������ ���� �������
	//static int chosen_button_id = 0;
	//chosen_button_id += input.moving_down_;
	//chosen_button_id -= input.moving_up_;
	int chosen_button_id = 0;

	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_);// ����� ��������� ������ � menusystem
		if (sys_output) {
			chosen_button_id = sys_output;
			//std::cout << "Chosen button id:" << chosen_button_id << std::endl;
		}
	}

	if (input.shoot_) {  ////////////////////////////// shoot �� �������, �������� �� mouce click
		switch (chosen_button_id)
		{
		case host_game_button_id:
			return GameStateId::HostMenu;
			break;
		case client_game_button_id:
			return GameStateId::ClientMenu;
			break;
		case single_game_button_id:
			return GameStateId::SingleMenu;
			break;
		default:
			return id_;
			break;
		}
	}

	return id_;
}

