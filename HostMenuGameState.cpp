#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"

HostMenuGameState::HostMenuGameState() {
	id_ = GameStateId::HostMenu;

	//// ����� ��������� ���� ���
	//BannerSpawner banner_spawner;
	//ButtonSpawner button_spawner;

	////����� ���� ��������� ����
	//Position banner_pos;
	//banner_pos.x = 0;
	//banner_pos.y = 0;

	//Entity* banner_ent = nullptr;

	//banner_ent = banner_spawner.Spawn(banner_pos, 'q');
	//banner_ent->setEntityID(1);

	//scene_.push_back(banner_ent);
	//addSystem(SystemId::MenuSystemId);
	//addSystem(SystemId::GraphicsSystemId);
	////addSystem(SystemId::MusicSystemId);


	////����� ������ ����� ��������� ����
	//Position back_button_pos;	// ��� ������ ����� ���������� ������ � ������� ����
	//back_button_pos.x = 200;
	//back_button_pos.y = 800;

	//Entity* back_button_ent = nullptr;

	//back_button_ent = button_spawner.Spawn(back_button_pos, 'b');
	//back_button_ent->setEntityID(1);

	//scene_.push_back(back_button_ent);
}

GameStateId HostMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}