#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include "SpawnID.h"
#include "InputHandler.h"
#include <iostream>
#include "GameSingleton.h"

HostMenuGameState::HostMenuGameState() {
	id_ = GameStateId::HostMenu;

	// ����� ��������� ���� ���
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;

	//����� ���� ��������� ����
	Position banner_pos(0, 0);


	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, host_banner);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);

	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	//addSystem(SystemId::MusicSystemId);b


	//����� ������ ����� ��������� ����
	Position back_button_pos(200, 800);	// ��� ������ ����� ���������� ������ � ������� ����


	temp_ent = button_spawner.Spawn(back_button_pos, back);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);

	// ����� ������ "������"
	Position connect_button_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_button_pos, play);
	scene_.push_back(temp_ent);

	// ����� ������ ����� �����. ��� ����� � ��� �������
	Position hull_1_pos(1300, 350);
	Position hull_2_pos(1650, 350);
	Position turret_1_pos(1300, 600);
	Position turret_2_pos(1650, 600);

	temp_ent = button_spawner.Spawn(hull_1_pos, tank_hull_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(hull_2_pos, tank_hull_2);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(turret_1_pos, tank_turret_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(turret_2_pos, tank_turret_2);
	scene_.push_back(temp_ent);


	setStateArgument(std::string("Maps/lvlTest2.txt"));
	Game::getInstance().setMyEntityId(2);

	for (int i = 0; i < 4; ++i) {
		Game::getInstance().setHullType(i, tank_hull_1);
		Game::getInstance().setTurretType(i, tank_turret_1);
	}
}

GameStateId HostMenuGameState::update(sf::RenderWindow& window) {

	//for (int i = 0; i < systems_.size(); ++i) {
	//	int sys_output = systems_[i]->update(window, scene_); // ��������� ����� ������ � menusystem
	//}


	Input input;
	input.handleInput(window);

	int chosen_button_id = 0;
	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_); // ��������� ����� ������ � menusystem
		if (sys_output) {
			chosen_button_id = sys_output;
		}
		//std::cout << chosen_button_id << std::endl;
	}
	// ������� ip � �������� �������� �����
	// �������� entity id 

	if (input.mouse_click_) { ////////////////////////////// shoot �� �������, �������� �� mouce click
		switch (chosen_button_id)
		{
		case play_button_id:
			return GameStateId::HostPlaying;
			break;
		case tank_hull_1_button_id:
			setTankHull(tank_hull_1);
			break;
		case tank_hull_2_button_id:
			setTankHull(tank_hull_2);
			break;
		case tank_turret_1_button_id:
			setTankTurret(tank_turret_1);
			break;
		case tank_turret_2_button_id:
			setTankTurret(tank_turret_2);
			break;
		case back_button_id:
			return GameStateId::MainMenu;
			break;
		default:
			return id_;
			break;
		}
	}


	return id_;
}