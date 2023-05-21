#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include "SpawnID.h"

SinglePlayerMenuGameState::SinglePlayerMenuGameState() {
	id_ = GameStateId::SingleMenu;

	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::MusicSystemId);

	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;


	//����� ���� ���������� ����
	Position banner_pos(0, 0);

	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, single_banner);//// ������ ���������� ���������
	scene_.push_back(temp_ent);


	//����� ������ �����
	Position back_button_pos(200, 800);	// ��� ������ ����� ���������� ������ � ������� ����


	temp_ent = button_spawner.Spawn(back_button_pos, back);
	scene_.push_back(temp_ent);

	// ����� ������ "������"
	Position connect_button_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_button_pos, play);
	scene_.push_back(temp_ent);
}

GameStateId SinglePlayerMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}

