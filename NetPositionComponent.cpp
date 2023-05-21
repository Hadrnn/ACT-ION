#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "netConnect.h"
#include "networkCodes.h"

void NetTankPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    
    PositionComponent new_component = *this; // �� ���� ��������� ����� 
    Position new_position = new_component.getPosition();
    std::vector<int> from_net_position = NetConnector::getInstance().get();

    while (from_net_position.size() >= 6) {
        if (from_net_position[5] != CHECKER) {
            from_net_position = NetConnector::getInstance().get();
            continue;
        }
        if (from_net_position[1] == TANK_POSITION_MARK) {
            new_position.x = from_net_position[2];
            new_position.y = from_net_position[3];
            new_position.rotation = from_net_position[4];
            break;
        }

        from_net_position = NetConnector::getInstance().get();
    }
    /// 
    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    if (my_collision) { /// ��������� ������� ���������� ������ ��� �������� ������������ ���������� 
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_position.rotation);
        *my_collision = new_collision;
    }
    setPosition(new_position);
}



void NetTurretPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    ObjectType currEntityType = scene[i]->getType();
    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    PositionComponent new_component = *original_component;
    Position new_position = new_component.getPosition();
    std::vector<int> from_net_position = NetConnector::getInstance().get();

    while (from_net_position.size() >= 6) {
        if (from_net_position[5] != CHECKER) {
            from_net_position = NetConnector::getInstance().get();
            continue;
        }
        if (currEntityType == ObjectType::Tank && from_net_position[1] == TANK_POSITION_MARK ||
            currEntityType == ObjectType::Bullet && from_net_position[1] == BULLET_POSITION_MARK ||
            currEntityType == ObjectType::Turret && from_net_position[1] == TURRET_POSITION_MARK) {

            new_position.x = from_net_position[2];
            new_position.y = from_net_position[3];
            new_position.rotation = from_net_position[4];

            break;
        }

        from_net_position = NetConnector::getInstance().get();
    }
    /// 
    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    if (my_collision) {
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_position.rotation);
        *my_collision = new_collision;
    }
    original_component->setPosition(new_position);
}

void NetBulletPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    ObjectType currEntityType = scene[i]->getType();
    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    PositionComponent new_component = *original_component;
    Position new_position = new_component.getPosition();
    std::vector<int> from_net_position = NetConnector::getInstance().get();

    while (from_net_position.size() >= 6) {
        if (from_net_position[5] != CHECKER) {
            from_net_position = NetConnector::getInstance().get();
            continue;
        }
        if (currEntityType == ObjectType::Tank && from_net_position[1] == TANK_POSITION_MARK ||
            currEntityType == ObjectType::Bullet && from_net_position[1] == BULLET_POSITION_MARK ||
            currEntityType == ObjectType::Turret && from_net_position[1] == TURRET_POSITION_MARK) {

            new_position.x = from_net_position[2];
            new_position.y = from_net_position[3];
            new_position.rotation = from_net_position[4];

            break;
        }

        from_net_position = NetConnector::getInstance().get();
    }
    /// 
    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    if (my_collision) {
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_position.rotation);
        *my_collision = new_collision;
    }
    original_component->setPosition(new_position);
}
