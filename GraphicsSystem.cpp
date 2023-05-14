#include "GraphicsSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"


void GraphicsSystem::renderScene(std::vector<Entity>& scene, sf::Window& window) {
    // ������� ������ ��� �������� ���� ���������
    std::vector<int> upper_layer;

    //������������ ������ ���� (�����) � ����������� �������� �������� ����
    for (int i = 0; i < scene.size(); ++i) {
        GraphicsComponent* current_graph = dynamic_cast<GraphicsComponent*>(scene[i].getComponentByID(ComponentID::GraphicsComponent));
        // ���������, ��� ���� ���������� ������ ���������� 
        if (!current_graph) continue;

        if (!current_graph->layer) {
            PositionComponent* current_pos = dynamic_cast<PositionComponent*>(scene[i].getComponentByID(ComponentID::PositionComponent));
            current_graph->getSprite()->setPosition(current_pos->getPosition()->x, current_pos->getPosition()->y);
        }
        else {
            upper_layer.push_back(i);
        }
    }

    // ������������ ������� ����
    for (int i = 0; i < upper_layer.size(); ++i) {
        GraphicsComponent* current_graph = dynamic_cast<GraphicsComponent*>(scene[upper_layer[i]].getComponentByID(ComponentID::GraphicsComponent));
        PositionComponent* current_pos = dynamic_cast<PositionComponent*>(scene[upper_layer[i]].getComponentByID(ComponentID::PositionComponent));

        if (current_pos->getRotation() >= 0) {
            current_graph->getSprite()->setRotation(current_pos->getRotation());
        }
        current_graph->getSprite()->setPosition(current_pos->getPosition()->x, current_pos->getPosition()->y);
    }
}