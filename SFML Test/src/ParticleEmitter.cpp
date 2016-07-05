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
	: particleAmount(particleAmount), particles(particleAmount), vertices(sf::Points, particleAmount), active(false) {

}

void ParticleEmitter::setOrigin(sf::Vector2f origin) {
	this->origin = origin;
}

void ParticleEmitter::update() {
	for (unsigned int i = 0; i < particleAmount; i++) {
		Particle& p = particles[i];
		p.update();

		vertices[i].color = sf::Color(255, 255, 255, 255 * p.getRemainingTime());
		if (p.getRemainingTime() > 0) {
			double distance = p.getSpeed() * ((1 - p.getRemainingTime()) * 500);
			vertices[i].position = sf::Vector2f(std::cos(p.getAngle()) * distance, std::sin(p.getAngle()) * distance) + origin + p.getOriginDelta();
		} else if (active) {
			p.spawn();
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
		particles[i].spawn();
		vertices[i].position = origin;
	}
}

void ParticleEmitter::end() {
	active = false;
}

bool ParticleEmitter::isActive() const {
	return active;
}
