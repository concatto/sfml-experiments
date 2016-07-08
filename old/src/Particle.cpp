/*
 * Particle.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "Particle.h"
#include "Utility.h"

Particle::Particle() {
	spawn();
}

void Particle::spawn(bool inverse, sf::Vector2f origin) {
	angle = Utility::random(2.9, 3.3);
	speed = Utility::random(5, 20);
	lifetime = Utility::random(1, 80);
	timeLeft = lifetime;
	originDelta = sf::Vector2f(Utility::random(-20, 20), Utility::random(-20, 20));

	if (inverse) angle = 3.14159 - angle;
	this->inverse = inverse;
	this->origin = origin;
}

void Particle::update() {
	if (timeLeft > 0) timeLeft--;
}

float Particle::getRemainingTime() const {
	return timeLeft / static_cast<float>(lifetime);
}

float Particle::getAngle() const {
	return angle;
}

float Particle::getSpeed() const {
	return speed;
}

bool Particle::isInverse() const {
	return inverse;
}

sf::Vector2f Particle::getOrigin() const {
	return origin;
}

sf::Vector2f Particle::getOriginDelta() const {
	return originDelta;
}

