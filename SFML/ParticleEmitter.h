/*
 * ParticleEmitter.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef PARTICLEEMITTER_H_
#define PARTICLEEMITTER_H_

#include "Particle.h"
#include "Updatable.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleEmitter : public sf::Drawable, public sf::Transformable, public Updatable {
private:
	unsigned int particleAmount;
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Vector2f origin;
	bool active;
	bool invert;

public:
	ParticleEmitter(unsigned int particleAmount);

	bool isActive() const;
	void start();
	void end();
	void setOrigin(sf::Vector2f origin);
	void setInvert(bool invert);
    virtual void update() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* PARTICLEEMITTER_H_ */
