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

public:
	ParticleEmitter(unsigned int particleAmount);

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
};

#endif /* PARTICLEEMITTER_H_ */
