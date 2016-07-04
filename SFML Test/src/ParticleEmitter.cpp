/*
 * ParticleEmitter.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(unsigned int particleAmount)
	: particleAmount(particleAmount), particles(particleAmount), vertices(sf::Points, particleAmount) {
	for (unsigned int i = 0; i < particleAmount; i++) {
		particles[i].//initialize
	}
}

void ParticleEmitter::update() {
	for (unsigned int i = 0; i < particleAmount; i++) {
		vertices[i].//update
	}
}

void ParticleEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) {
	update();
	target.draw(vertices, states);
}

