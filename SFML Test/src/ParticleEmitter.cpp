/*
 * ParticleEmitter.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "ParticleEmitter.h"
#include "Utility.h"
#include <cmath>
#include <iostream>

ParticleEmitter::ParticleEmitter(unsigned int particleAmount)
	: particleAmount(particleAmount), particles(particleAmount), vertices(sf::Points, particleAmount), active(false), invert(false) {

}

void ParticleEmitter::setOrigin(sf::Vector2f origin) {
	this->origin = origin;
}

void ParticleEmitter::setInvert(bool invert) {
	this->invert = invert;
}

void ParticleEmitter::update() {
	for (unsigned int i = 0; i < particleAmount; i++) {
		Particle& p = particles[i];
		p.update();

		vertices[i].color = sf::Color(255, 255, 255, 255 * p.getRemainingTime());
		if (p.getRemainingTime() > 0) {
			double distance = p.getSpeed() * ((1 - p.getRemainingTime()) * 20);
			double angle = p.getAngle();
			double fix = p.isInverse() ? -152 : 0;

			vertices[i].position = sf::Vector2f(std::cos(angle) * distance, std::sin(angle) * distance) + p.getOrigin() + p.getOriginDelta() + sf::Vector2f(fix, 0);
		} else if (active) {
			p.spawn(invert, origin);
			vertices[i].position = origin;
		}
	}
}

void ParticleEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(vertices, states);
}

void ParticleEmitter::start() {
	active = true;
	for (unsigned int i = 0; i < particleAmount; i++) {
		particles[i].spawn(invert, origin);
		vertices[i].position = origin;
	}
}

void ParticleEmitter::end() {
	active = false;
}

bool ParticleEmitter::isActive() const {
	return active;
}
