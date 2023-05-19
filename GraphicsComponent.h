#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"

class GraphicsComponent : public Component {
public:
    GraphicsComponent() = default;

    bool layer = 0;

    void setAliveImage(sf::Image aliveimage) { 
        obj_image_ = aliveimage;
        obj_image_.createMaskFromColor(sf::Color::White);
        alive_texture_.loadFromImage(obj_image_);
        obj_sprite_.setTexture(alive_texture_);

        obj_sprite_.setScale(0.5f, 0.5f);
        obj_sprite_.setOrigin(50, 50);
        //��������, ���� ���� �������� ����������� ������. ���� �� ������� ��� ���������� ��� ����
    };

    void setOrigin(int x, int y) {
        obj_sprite_.setOrigin(x, y);
    }

    void setTexture(sf::Texture texture);

    void setSprite(sf::Sprite sprite);

    bool checkBullet(Position beg, Position end);// �������� � ������� ����� ��� 

    sf::Sprite getSprite() { return obj_sprite_; }
    /*sf::Texture getTexture() { return obj_texture_; }*/

private:
    sf::Image obj_image_;
    sf::Texture alive_texture_;
    sf::Texture dead_texture_;
    sf::Sprite obj_sprite_;
};
