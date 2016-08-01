/*
 * ParticleEmitter.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "ParticleEmitter2.h"
#include "Utility.h"
#include <cmath>
#include <iostream>

ParticleEmitter2::ParticleEmitter2(unsigned int particleAmount)
    : particleAmount(particleAmount), particles(particleAmount), vertices(sf::Triangles, particleAmount * 3), active(false), invert(false) {

}

void ParticleEmitter2::setOrigin(sf::Vector2f origin) {
	float xOffset = 20;
	float yOffset = 55;
	this->origin = origin + sf::Vector2f(xOffset * (invert ? -1 : 1), yOffset);
}

void ParticleEmitter2::setInvert(bool invert) {
	this->invert = invert;
}

void ParticleEmitter2::update() {
	for (unsigned int i = 0; i < particleAmount; i++) {
        updateTriangle(i);
	}
}

void ParticleEmitter2::updateTriangle(unsigned int i) {
    Particle2& p = particles[i];
    p.update();

    i *= 3;

    if (p.getRemainingTime() > 0) {
        double angles[] = {
            Utility::pi(1, 2),
            Utility::pi(11, 6),
            Utility::pi(7, 6)
        };

        for (int k = 0; k < 3; k++) {
            unsigned int a = i + k;
            vertices[a].color = sf::Color(255, 235 * p.getRemainingTime() + 20, 255 * (p.getRemainingTime() / 2.0), 255 * p.getRemainingTime());

            double distance = p.getSpeed() * ((1 - p.getRemainingTime()) * 20);
            float angle = angles[k] + p.getRotation();

            float x = std::cos(p.getAngle()) * distance + std::cos(angle) * p.getSize();
            float y = std::sin(p.getAngle()) * distance + std::sin(angle) * p.getSize();

            vertices[a].position = sf::Vector2f(x, y) + p.getOrigin() + p.getOriginDelta();
        }
    } else if (active) {
        spawnParticle(p);
    } else {
        for (int k = 0; k < 3; k++) {
            unsigned int a = i + k;
            vertices[a].color = sf::Color::Transparent;
        }
    }
}

void ParticleEmitter2::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(vertices, states);
}

void ParticleEmitter2::start() {
	active = true;
	for (unsigned int i = 0; i < particleAmount; i++) {
        spawnParticle(particles[i]);
        //vertices[i].position = origin;
	}
}

void ParticleEmitter2::spawnParticle(Particle2& p) {
    p.spawn(Utility::random(Utility::pi(7, 4), Utility::pi(5, 4)), Utility::random(12, 25), Utility::random(0.05, 0.2), Utility::random(18, 30), invert, origin);
}

void ParticleEmitter2::end() {
	active = false;
}

bool ParticleEmitter2::isActive() const {
	return active;
}

void ParticleEmitter2::setActive(bool active) {
    this->active = active;
}
