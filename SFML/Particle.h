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
	sf::Vector2f origin;
	bool inverse;

public:
	Particle();

	void spawn(bool inverse = false, sf::Vector2f origin = sf::Vector2f());
	void update();
	float getRemainingTime() const;
	float getAngle() const;
	float getSpeed() const;
	bool isInverse() const;
	sf::Vector2f getOrigin() const;
	sf::Vector2f getOriginDelta() const;
};

#endif /* PARTICLE_H_ */
