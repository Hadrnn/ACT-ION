#pragma once
#include "GameState.h"
#include "MusicSystem.h"
#include "GraphicsSystem.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>
#include <iostream>
#include <Windows.h>


ClientPlayingGameState::ClientPlayingGameState() {
	id_ = GameStateId::ClientPlaying;

	const int block_size = 50; ////////����� ���-�� ����� ��������

	int map_width = 0;
	int map_height = 0;

	MapSpawner ws;
	TankSpawner ts;
	BannerSpawner bs;
	TurretSpawner tr;
	//scene.push_back(bs.Spawn(Position(0, 0), 's')[0]); /// menu music

	std::ifstream map_file("Maps/lvlTest2.txt");

	map_file >> map_width;
	map_file >> map_height;

	/// map generation
	for (int i = 0; i < map_height; ++i)
		for (int j = 0; j < map_width; ++j) {
			char current_block = 0;
			map_file >> current_block;

			Position curr_pos;
			curr_pos.x = j * block_size + int(block_size / 2);
			curr_pos.y = i * block_size + int(block_size / 2);
			Entity temp_ent;

			switch (current_block) {
			case 'w':
				temp_ent = ws.Spawn(curr_pos, 'w');
				temp_ent.setEntityID(i * map_width + j);
				scene_.push_back(temp_ent);
				break;
			case's':
				temp_ent = ws.Spawn(curr_pos, 's');
				temp_ent.setEntityID(i * map_width + j);
				scene_.push_back(temp_ent);
				break;
			case'd':
				temp_ent = ws.Spawn(curr_pos, 'd');
				temp_ent.setEntityID(i * map_width + j);
				scene_.push_back(temp_ent);
				break;
			default:
				break;
			}
		}
	
	/// tank spawn 
	{
		int tank_x = 0;
		int tank_y = 0;

		map_file >> tank_x >> tank_y;
		Position curr_pos;
		curr_pos.x = tank_y * block_size + int(block_size / 2);
		curr_pos.y = tank_y * block_size + int(block_size / 2);

		Entity temp_ent;
		temp_ent = ts.Spawn(curr_pos, '1');
		scene_.push_back(temp_ent);
		{
			PositionComponent* tank_pos = dynamic_cast<PositionComponent*>(temp_ent.getComponentByID(ComponentID::PositionComponent));
			temp_ent = tr.Spawn(curr_pos, '1');
			PositionComponent* turr_pos = dynamic_cast<PositionComponent*>(temp_ent.getComponentByID(ComponentID::PositionComponent));
			turr_pos->setParent(tank_pos);
		}
		scene_.push_back(temp_ent);
	}


	//addSystem(SystemId::MusicSystemId, new MusicSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);
	addSystem(SystemId::PhysicsSystemId, new PhysicsSystem);


	//ms.playMusic(scene); menu music
}

GameState* ClientPlayingGameState::update(sf::RenderWindow& window) {



	////
	getSystemById(SystemId::PhysicsSystemId)->update(window, scene_);
	getSystemById(SystemId::GraphicsSystemId)->update(window, scene_);
	////

	Entity* my_tank = getMyTank();

	if (isDead(my_tank) && !window.isOpen()) {
		
		return new MainMenuGameState();
	}

	return this;
}

Entity* ClientPlayingGameState::getMyTank() {
    Entity* my_tank = nullptr;

    for (int i = 0; i < scene_.size(); ++i) {
        if (scene_[i].getEntityID() == -1 && scene_[i].getType() == ObjectType::Tank)
            my_tank = &scene_[i];
    }
    return my_tank;
}


bool ClientPlayingGameState::isDead(Entity* tank) {
	return false;

	if (!tank)
		return false;

    HealthComponent* health_component = dynamic_cast<HealthComponent*>(tank->getComponentByID(ComponentID::HealthComponent));
    return health_component->getHealth() > 0;
}
