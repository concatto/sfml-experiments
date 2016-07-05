/*
 * ParticleEmitter.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef PARTICLEEMITTER_H_
#define PARTICLEEMITTER_H_

#include "Particle.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleEmitter : public sf::Drawable, public sf::Transformable {
private:
	unsigned int particleAmount;
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Vector2f origin;
	bool active;

public:
	ParticleEmitter(unsigned int particleAmount);

	bool isActive() const;
	void start();
	void end();
	void setOrigin(sf::Vector2f origin);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* PARTICLEEMITTER_H_ */
