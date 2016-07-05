/*
 * Particle.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <SFML/Graphics.hpp>

class Particle {
private:
	float angle;
	float speed;
	unsigned int lifetime;
	unsigned int timeLeft;
	sf::Vector2f originDelta;

public:
	Particle();

	void spawn();
	void update();
	float getRemainingTime() const;
	float getAngle() const;
	float getSpeed() const;
	sf::Vector2f getOriginDelta() const;
};

#endif /* PARTICLE_H_ */
