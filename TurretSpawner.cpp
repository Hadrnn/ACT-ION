#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "SoundComponent.h"
#include "ShootComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include "SpawnID.h"

Entity* TurretSpawner::Spawn(Position position, int subType) {
	static sf::Image img;//// ������ ������???
	sf::SoundBuffer buffer;
	PositionComponent* pos_to_add = nullptr;

	switch (current_type_)
	{
	case OwnerType::Network:
		pos_to_add = new NetTurretPositionComponent();
		break;
	case OwnerType::Bot:
		pos_to_add = new BotTurretPositionComponent();
		break;
	case OwnerType::Player:
		pos_to_add = new TurretPositionComponent();
		break;
	default:
		break;
	}

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	ShootComponent* shoot_to_add = new ShootComponent();
	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);


	Entity* to_add = new Entity(ObjectType::Turret);

	graph_to_add = new GraphicsComponent();

	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case tank_turret_1: // tank type 1
		img.loadFromFile("Image/tank_1_gun_100_100.png");
		graph_to_add->setAliveImage(img);
		shoot_to_add->setCooldown(1.0);
		shoot_to_add->setBulletType(bullet_1);
		//buffer.loadFromFile("Sound/Shot1.wav");
		//sound_to_add->setSound(SoundType::ShootingSound, buffer);
		break;

	case tank_turret_2: // tank type 1
		img.loadFromFile("Image/tank_2_gun_100_100.png");
		graph_to_add->setAliveImage(img);
		shoot_to_add->setCooldown(1.0);
		shoot_to_add->setBulletType(bullet_2);
		break;

	default:
		break;
	}

	graph_to_add->layer = true;
	to_add->putComponent(ComponentID::ShootComponent, shoot_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	//to_add->putComponent(ComponentID::SoundComponent, sound_to_add);
	return to_add;
}
