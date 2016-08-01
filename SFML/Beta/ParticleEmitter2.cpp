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

ParticleEmitter2::ParticleEmitter2(unsigned int particleAmount, const sf::Texture& texture)
    : texture(texture), particleAmount(particleAmount), particles(particleAmount), vertices(sf::Quads, particleAmount * 4), active(false), invert(false) {

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
        updateParticle(i);
	}
}

void ParticleEmitter2::updateParticle(unsigned int i) {
    Particle2& p = particles[i];
    p.update();
    int count = 4;

    i *= count;

    if (p.getRemainingTime() > 0) {
        double angles[] = {
            /*Utility::pi(1, 2),
            Utility::pi(11, 6),
            Utility::pi(7, 6)*/
            Utility::pi(7, 4),
            Utility::pi(5, 4),
            Utility::pi(3, 4),
            Utility::pi(1, 4)
        };

        float xs[] = {0, 104, 104, 0};
        float ys[] = {0, 0, 104, 104};

        float brightness = p.getBrightness();
        for (int k = 0; k < count; k++) {
            unsigned int a = i + k;
            vertices[a].color = sf::Color(brightness, brightness, brightness, 255 * p.getRemainingTime());

            double distance = p.getSpeed() * ((1 - p.getRemainingTime()) * 20);
            float angle = angles[k] + p.getRotation();

            float x = std::cos(p.getAngle()) * distance + std::cos(angle) * p.getSize();
            float y = std::sin(p.getAngle()) * distance + std::sin(angle) * p.getSize();

            vertices[a].position = sf::Vector2f(x, y) + p.getOrigin() + p.getOriginDelta();
            vertices[a].texCoords = sf::Vector2f(xs[k], ys[k]);
        }
    } else if (active) {
        spawnParticle(p);
    } else {
        for (int k = 0; k < count; k++) {
            unsigned int a = i + k;
            vertices[a].color = sf::Color::Transparent;
        }
    }
}

void ParticleEmitter2::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
    states.texture = &texture;
	target.draw(vertices, states);
}

void ParticleEmitter2::start() {
	active = true;
    /*for (unsigned int i = 0; i < particleAmount; i++) {
        spawnParticle(particles[i]);
        //vertices[i].position = origin;
    }*/
}

void ParticleEmitter2::spawnParticle(Particle2& p) {
    p.spawn(Utility::random(Utility::pi(7, 4), Utility::pi(5, 4)), Utility::random(12, 25), Utility::random(0.03, 0.17), Utility::random(50, 60), invert, origin);
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
