/*
 * Character.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include <iostream>
#include "Character.h"

Character::Character(const sf::Texture& texture, sf::Vector2u sizeBounds)
    : sf::Sprite(texture), sizeBounds(sizeBounds), animationManager(*this) {

    animationManager.loadAnimations({
        {sf::IntRect(1240, 0, 124, 77)},
        AnimationManager::generateFrames(sf::Vector2i(124, 77), 10)
    });

    stand();
    animationManager.beginAnimation(0);
    sf::IntRect rect = getTextureRect();
    setOrigin(rect.width / 2.0, 0);
}

void Character::update() {
    setScale(facingRight ? 1 : -1, 1);
    animationManager.update();
}

void Character::stand() {
    if (getState(State::Walk)) {
        unsetState(State::Walk);
        animationManager.beginAnimation(0);
    }
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
    animationManager.setSpeed(AnimationManager::Fast);
}

void Character::slow() {
    movementSpeed = Speed::Normal;
    animationManager.setSpeed(AnimationManager::Normal);
}

void Character::moveLeft() {
    facingRight = false;
    walk();
}

void Character::moveRight() {
    facingRight = true;
    walk();
}

void Character::walk() {
    if (!getState(Walk)) {
        setState(State::Walk);
        animationManager.beginAnimation(1);
    }
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
