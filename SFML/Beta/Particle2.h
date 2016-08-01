/*
 * Particle.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef PARTICLE2_H_
#define PARTICLE2_H_

#include "Updatable.h"
#include <SFML/Graphics.hpp>

class Particle2 : public Updatable {
private:
    float brightness;
	float angle;
	float speed;
    float rotationSpeed;
    float rotation;
    float size;
    unsigned int lifetime = 0;
    unsigned int timeLeft = 0;
	sf::Vector2f originDelta;
	sf::Vector2f origin;
    bool inverse = false;

public:
    Particle2();

    void spawn(float angle, float speed, float rotationSpeed, float size, bool inverse = false, sf::Vector2f origin = sf::Vector2f());
    virtual void update() override;
	float getRemainingTime() const;
    float getBrightness() const;
	float getAngle() const;
	float getSpeed() const;
    float getRotation() const;
    float getSize() const;
	bool isInverse() const;
	sf::Vector2f getOrigin() const;
	sf::Vector2f getOriginDelta() const;
};

#endif /* PARTICLE_H_ */
