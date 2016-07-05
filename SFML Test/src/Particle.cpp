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

void Particle::spawn() {
	angle = Utility::random(2.3, 3.7);
	speed = Utility::random(1, 10);
	lifetime = Utility::random(1, 100);
	timeLeft = lifetime;
	originDelta = sf::Vector2f(Utility::random(-6, 6), Utility::random(-20, 20));
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

sf::Vector2f Particle::getOriginDelta() const {
	return originDelta;
}

