/*
 * Character.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include <iostream>
#include "Character.h"

std::vector<Animation> Character::animations{
	Animation({sf::IntRect(1240, 0, 124, 77)}, Animation::Normal),
	Animation(Animation::generateFrames(10, sf::Vector2i(124, 77)), Animation::Normal)
};


Character::Character(const sf::Texture& texture, sf::Vector2u sizeBounds)
	: sf::Sprite(texture), state(State::None), animationIndex(-1), animationPlaying(false), facingRight(true), movementSpeed(5), sizeBounds(sizeBounds) {

	stand();

	sf::IntRect rect = getTextureRect();
	setOrigin(rect.width / 2.0, 0);
}

void Character::update() {
	if (animationPlaying) {
		animations[animationIndex].update(*this);
	}

	if (getState(State::Walk)) {
		move(movementSpeed * (facingRight ? 1 : -1), 0);
	}

	setScale(facingRight ? 1 : -1, 1);

    if (!getState(State::Ground)) {
        move(0, -force);
        force -= 0.35;
    }
}

void Character::stand() {
    unsetState(State::Walk);
}

//jsfiddle.net/LyM87
void Character::jump()
{
    if (getState(State::Ground)) {
        this->force = 9;
        unsetState(State::Ground);
    }
}

void Character::accelerate() {
	Character::animations[State::Walk].setUpdateRate(Animation::Fast);
	movementSpeed = Speed::Fast;
}

void Character::slow() {
	Character::animations[State::Walk].setUpdateRate(Animation::Normal);
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

void Character::playAnimation(unsigned int index) {
	if (index == animationIndex) return;

	animationIndex = index;
	animationPlaying = true;
	animations[index].start(*this);
}

bool Character::isFacingRight() const {
	return facingRight;
}

sf::Vector2u Character::getSizeBounds() const {
    return sizeBounds;
}

sf::IntRect Character::getBoundingBox() const
{
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

void Character::notifyGroundDistance(int distance)
{
    if (distance < -force) {
        move(0, distance);
        setState(State::Ground);
        force = 0;
    } else {
        unsetState(State::Ground);
    }
}

void Character::notifyCeilingDistance(int distance)
{
    if (distance < force) {
        move(0, -distance);
        force = 0;
    }
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
