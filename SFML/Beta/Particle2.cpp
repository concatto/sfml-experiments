/*
 * Particle2.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "Particle2.h"
#include "Utility.h"

Particle2::Particle2() {

}

void Particle2::spawn(float angle, float speed, float rotationSpeed, float size, bool inverse, sf::Vector2f origin) {
    this->angle = angle;
    this->speed = speed;
    this->rotationSpeed = rotationSpeed;
    this->size = size;
    lifetime = Utility::random(1, 200);
    rotation = 0;
	timeLeft = lifetime;
    originDelta = sf::Vector2f(Utility::random(-60, 60), Utility::random(-60, 60));
    brightness = Utility::random(160, 255);

    if (inverse) this->angle = Utility::pi() - angle;
	this->inverse = inverse;
	this->origin = origin;
}

void Particle2::update() {
	if (timeLeft > 0) timeLeft--;

    rotation += rotationSpeed;
    if (rotation > Utility::pi(2)) {
        rotation = 0;
    }
}

float Particle2::getRemainingTime() const {
    return timeLeft / static_cast<float>(lifetime);
}

float Particle2::getBrightness() const
{
    return brightness;
}

float Particle2::getAngle() const {
	return angle;
}

float Particle2::getSpeed() const {
    return speed;
}

float Particle2::getRotation() const
{
    return rotation;
}

float Particle2::getSize() const
{
    return size;
}

bool Particle2::isInverse() const {
	return inverse;
}

sf::Vector2f Particle2::getOrigin() const {
	return origin;
}

sf::Vector2f Particle2::getOriginDelta() const {
	return originDelta;
}
