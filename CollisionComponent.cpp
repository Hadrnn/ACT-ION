#pragma once
#include "Entity.h"
#include "Component.h"
#include <math.h>
#include "CollisionComponent.h"


const double EPS = 1E-9;

int det(int a, int b, int c, int d) {
    return a * d - b * c;
}

bool between(int a, int b, double c) {
    return std::min(a, b) <= c + EPS && c <= std::max(a, b) + EPS;
}

bool intersect_1(int a, int b, int c, int d) {
    if (a > b)  std::swap(a, b);
    if (c > d)  std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

bool intersect(Position a, Position b, Position c, Position d) {
    int A1 = a.y - b.y, B1 = b.x - a.x, C1 = -A1 * a.x - B1 * a.y;
    int A2 = c.y - d.y, B2 = d.x - c.x, C2 = -A2 * c.x - B2 * c.y;
    int zn = det(A1, B1, A2, B2);
    if (zn != 0) {
        double x = -det(C1, B1, C2, B2) * 1. / zn;
        double y = -det(A1, C1, A2, C2) * 1. / zn;
        return between(a.x, b.x, x) && between(a.y, b.y, y)
            && between(c.x, d.x, x) && between(c.y, d.y, y);
    }
    else
        return det(A1, C1, A2, C2) == 0 && det(B1, C1, B2, C2) == 0
        && intersect_1(a.x, b.x, c.x, d.x)
        && intersect_1(a.y, b.y, c.y, d.y);
}

int distance_coll(Position a, Position b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

CollisionComponent::CollisionComponent(Position position, int rotation, int height, int width) {
    position_ = position;
    rotation_ = rotation;
    height_ = height / 2;
    width_ = width / 2;
    for (int i = 0; i < 4; i++) {
        hitbox_.push_back(position_);
    }
    double angle = rotation * 3.14 / 180;
    hitbox_[0].x = position_.x + cos(angle) * (height_)-cos(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[1].x = position_.x + cos(angle) * (height_)+cos(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[2].x = position_.x - cos(angle) * (height_)+cos(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[3].x = position_.x - cos(angle) * (height_)-cos(90 * 3.14 / 180 - angle) * (width_);

    hitbox_[0].y = position_.y + sin(angle) * (height_)+sin(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[1].y = position_.y + sin(angle) * (height_)-sin(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[2].y = position_.y - sin(angle) * (height_)-sin(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[3].y = position_.y - sin(angle) * (height_)+sin(90 * 3.14 / 180 - angle) * (width_);
}

void CollisionComponent::update(Position position, int rotation) {
    position_ = position;
    rotation_ = rotation;
    double angle = rotation * 3.14 / 180;
    hitbox_[0].x = position_.x + cos(angle) * (height_)-cos(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[1].x = position_.x + cos(angle) * (height_)+cos(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[2].x = position_.x - cos(angle) * (height_)+cos(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[3].x = position_.x - cos(angle) * (height_)-cos(90 * 3.14 / 180 - angle) * (width_);

    hitbox_[0].y = position_.y + sin(angle) * (height_)+sin(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[1].y = position_.y + sin(angle) * (height_)-sin(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[2].y = position_.y - sin(angle) * (height_)-sin(90 * 3.14 / 180 - angle) * (width_);
    hitbox_[3].y = position_.y - sin(angle) * (height_)+sin(90 * 3.14 / 180 - angle) * (width_);
}

bool CollisionComponent::checkCollision(CollisionComponent* tested_object) {
    std::vector<Position> temp_hitbox_this = this->get_hitbox();
    temp_hitbox_this.push_back(temp_hitbox_this[0]);
    std::vector<Position> temp_hitbox_in = tested_object->get_hitbox();
    temp_hitbox_in.push_back(temp_hitbox_in[0]);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (intersect(temp_hitbox_this[i], temp_hitbox_this[i + 1], temp_hitbox_in[j], temp_hitbox_in[j + 1])) {
                return false;
            }
        }
    }
    if (distance_coll(position_, tested_object->position_) < std::min(tested_object->width_, tested_object->height_) ||
        distance_coll(position_, tested_object->position_) < std::min(width_, height_)) {
        return false;
    }
    return true;
}

bool CollisionComponent::checkBullet(Position beg, Position end) {
    std::vector<Position> temp_hitbox_this = this->get_hitbox();
    temp_hitbox_this.push_back(temp_hitbox_this[0]);
    for (int i = 0; i < 4; i++) {
        if (intersect(temp_hitbox_this[i], temp_hitbox_this[i + 1], beg, end)) {
            return false;
        }
    }
    return true;
}

void CollisionComponent::setPosition(Position& position) {
    position_ = position; 
}

void CollisionComponent::setRotation(const int& coner) {
    rotation_ = coner;
}

std::vector<Position> CollisionComponent::get_hitbox() {
    return hitbox_;
}
