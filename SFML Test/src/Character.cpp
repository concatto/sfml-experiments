/*
 * Character.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "Character.h"

std::vector<Animation> Character::animations{
	Animation({sf::IntRect(1240, 0, 124, 77)}, Animation::Normal),
	Animation(Animation::generateFrames(10, sf::Vector2i(124, 77)), Animation::Normal)
};


Character::Character(const sf::Texture& texture, sf::IntRect boundingBox)
	: sf::Sprite(texture), animationIndex(0), animationPlaying(false), facingRight(true), movementSpeed(5), boundingBox(boundingBox) {

}

void Character::update() {
	if (animationPlaying) {
		animations[animationIndex].update(*this);
	}
}

void Character::stand() {
	playAnimation(State::Stand);
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
	playAnimation(State::Walk);

	if (facingRight) {
		facingRight = false;
		setScale(-1, 1);
		move(124, 0);
	}
	move(-movementSpeed, 0);
}

void Character::moveRight() {
	playAnimation(State::Walk);

	if (!facingRight) {
		facingRight = true;
		setScale(1, 1);
		move(-124, 0);
	}
	move(movementSpeed, 0);
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

sf::IntRect Character::getBoundingBox() const {
	return boundingBox;
}

void Character::draw(sf::RenderTarget& target) {
	sf::RectangleShape box(sf::Vector2f(boundingBox.width, boundingBox.height));
	box.setPosition(this->getPosition() + sf::Vector2f(boundingBox.top, boundingBox.left));
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(3);
	target.draw(box);
}
