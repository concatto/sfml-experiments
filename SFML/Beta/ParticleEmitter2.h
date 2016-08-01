/*
 * ParticleEmitter.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef PARTICLEEMITTER2_H_
#define PARTICLEEMITTER2_H_

#include "Particle2.h"
#include "Updatable.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleEmitter2 : public sf::Drawable, public sf::Transformable, public Updatable {
private:
	unsigned int particleAmount;
    std::vector<Particle2> particles;
	sf::VertexArray vertices;
	sf::Vector2f origin;
	bool active;
	bool invert;

    void updateTriangle(unsigned int i);
    void spawnParticle(Particle2& p);

public:
    ParticleEmitter2(unsigned int particleAmount);

	bool isActive() const;
	void start();
	void end();
	void setOrigin(sf::Vector2f origin);
	void setInvert(bool invert);
    virtual void update() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setActive(bool active);
};

#endif /* PARTICLEEMITTER_H_ */
