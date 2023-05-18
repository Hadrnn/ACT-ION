#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"
#include "GraphicsSystem.h"

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

	Entity banner_ent;

	banner_ent = banner_spawner.Spawn(banner_pos, 'm');
	banner_ent.setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);


	//����� ������ host game �������� ����
	Position host_game_pos;
	host_game_pos.x = 200;  //��� ������������ ���� ������ � ����������� �� ������� ������
	host_game_pos.y = 800;

	Entity host_game_ent;

	host_game_ent = button_spawner.Spawn(host_game_pos, 'h');
	host_game_ent.setEntityID(1);

	scene_.push_back(host_game_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);

	//����� ������ connect to game �������� ����
	Position connect_game_pos;
	connect_game_pos.x = 1400;  //��� ������������ ���� ������ � ����������� �� ������� ������
	connect_game_pos.y = 800;

	Entity connect_game_ent;

	connect_game_ent = button_spawner.Spawn(connect_game_pos, 'c');
	connect_game_ent.setEntityID(1);

	scene_.push_back(connect_game_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);
}



GameState* MainMenuGameState::update(sf::RenderWindow& window) {

	static int chosen_button_id = 0;
	Input input;
	input.handleInput(window);
	//chosen_button_id += input.moving_down_;
	//chosen_button_id -= input.moving_up_;

	getSystemById(SystemId::GraphicsSystemId)->update(window, scene_);

	MenuSystem ms;

	int mouce_choose = ms.update(window,scene_);
	if (mouce_choose) {
		chosen_button_id = mouce_choose;
		//std::cout << "Chosen button id:" << chosen_button_id << std::endl;
	}

	if (input.shoot_) {
		switch (chosen_button_id)
		{
		case 1:
			return new HostPlayingGameState();// mageer, chanfge state to (host play)
			break;
		case 2:
			return new ClientPlayingGameState();
		default:
			return this;
			break;
		}
	}

	return this;
}

