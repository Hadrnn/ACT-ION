#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "netConnect.h"
#include "networkCodes.h"

void NetTankPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {

    PositionComponent new_component = *this; // �� ���� ��������� ����� 
    Position new_position = new_component.getPosition();
    package from_net_position = NetConnector::getInstance().getPosition();

    int current_entity_id = scene[i]->getEntityID();

    while (from_net_position) {
        if (from_net_position.eventType_ != TANK_POSITION_MARK) {
            from_net_position = NetConnector::getInstance().getPosition();
        }
        else {
            if (current_entity_id == from_net_position.id_) {
                new_position.x = from_net_position.info1_;
                new_position.y = from_net_position.info2_;
                new_position.rotation = from_net_position.info3_;

                CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
                if (my_collision) { /// ��������� ������� ���������� ������ ��� �������� ������������ ���������� 
                    CollisionComponent new_collision = *my_collision;
                    new_collision.update(new_position, new_position.rotation);
                    *my_collision = new_collision;
                }
                setPosition(new_position);
                break;
            }
            else {
                from_net_position = NetConnector::getInstance().getPosition();
            }
        }
    }
}



void NetTurretPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    PositionComponent new_component = *this;
    Position new_position = new_component.getPosition();
    package from_net_position = NetConnector::getInstance().getPosition();

    int current_entity_id = scene[i]->getEntityID();

    while (from_net_position) {
        if (from_net_position.eventType_ != TURRET_POSITION_MARK) {
            from_net_position = NetConnector::getInstance().getPosition();
        }
        else {
            if (current_entity_id == from_net_position.id_) {

                new_position.x = from_net_position.info1_;
                new_position.y = from_net_position.info2_;
                new_position.rotation = from_net_position.info3_;
                //std::cout << from_net_position.info3_;
                setRotation(new_position.rotation);
                setPosition(new_position);
                break;
            }
            else {
                from_net_position = NetConnector::getInstance().getPosition();
            }
        }
    }
}

void NetBulletPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    PositionComponent new_component = *this;
    Position new_position = new_component.getPosition();
    package from_net_position = NetConnector::getInstance().getPosition();

    int current_entity_id = scene[i]->getEntityID();

    while (from_net_position) {
        if (from_net_position.eventType_ != BULLET_POSITION_MARK) {
            from_net_position = NetConnector::getInstance().getPosition();
        }
        else {
            if (current_entity_id == from_net_position.id_) {

                new_position.x = from_net_position.info1_;
                new_position.y = from_net_position.info2_;
                new_position.rotation = from_net_position.info3_;
                //std::cout << from_net_position.info3_;
                setRotation(new_position.rotation);
                setPosition(new_position);
                break;
            }
            else {
                from_net_position = NetConnector::getInstance().getPosition();
            }
        }
    }
}
