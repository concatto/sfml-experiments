/*
 * Character.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include <iostream>
#include "Character.h"

std::vector<Animation> Character::animations {
    Animation({sf::IntRect(1240, 0, 124, 77)}, Animation::Normal),
    Animation(Animation::generateFrames(10, sf::Vector2i(124, 77)), Animation::Normal)
};


Character::Character(const sf::Texture& texture, sf::Vector2u sizeBounds)
    : sf::Sprite(texture), state(State::None), facingRight(true), movementSpeed(Speed::Normal), sizeBounds(sizeBounds) {

    stand();

    sf::IntRect rect = getTextureRect();
    setOrigin(rect.width / 2.0, 0);
}

void Character::update() {
    setScale(facingRight ? 1 : -1, 1);

}

void Character::stand() {
    unsetState(State::Walk);
}

//jsfiddle.net/LyM87
void Character::jump() {
    if (getState(State::Ground)) {
        this->verticalForce = 12;
        unsetState(State::Ground);
    }
}

void Character::accelerate() {
    movementSpeed = Speed::Fast;
}

void Character::slow() {
    movementSpeed = Speed::Normal;
}

void Character::moveLeft() {
    setState(State::Walk);
    facingRight = false;
}

void Character::moveRight() {
    setState(State::Walk);
    facingRight = true;
}

bool Character::isFacingRight() const {
    return facingRight;
}

float Character::getVerticalForce() const {
    return verticalForce;
}

float Character::getMovementSpeed() const {
    return movementSpeed;
}

void Character::setVerticalForce(float verticalForce) {
    this->verticalForce = verticalForce;
}

sf::Vector2u Character::getSizeBounds() const {
    return sizeBounds;
}

sf::IntRect Character::getBoundingBox() const {
    sf::Vector2f pos = getPosition();
    return sf::IntRect(pos.x - (sizeBounds.x / 2.0), pos.y + (getTextureRect().height - sizeBounds.y), sizeBounds.x, sizeBounds.y);
}

void Character::draw(sf::RenderTarget& target) {
    sf::RectangleShape box;
    sf::IntRect boundingBox = getBoundingBox();
    box.setPosition(boundingBox.left, boundingBox.top);
    box.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineColor(sf::Color::Red);
    box.setOutlineThickness(3);

    target.draw(box);
}

void Character::setState(State s) {
    state = state | s;
}

void Character::unsetState(State s) {
    state = state & (~s);
}

bool Character::getState(State s) const {
    return (state & s) != 0;
}
