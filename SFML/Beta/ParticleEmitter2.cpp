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
    unsigned int a = i;
    unsigned int b = i + 1;
    unsigned int c = i + 2;

    float aa = Utility::pi(1, 2) + p.getRotation();
    float ab = Utility::pi(11, 6) + p.getRotation();
    float ac = Utility::pi(7, 6) + p.getRotation();

    vertices[a].color = sf::Color(255, 255, 255, 255 * p.getRemainingTime());
    vertices[b].color = sf::Color(255, 255, 255, 255 * p.getRemainingTime());
    vertices[c].color = sf::Color(255, 255, 255, 255 * p.getRemainingTime());
    if (p.getRemainingTime() > 0) {
        double distance = p.getSpeed() * ((1 - p.getRemainingTime()) * 20);
        double angle = p.getAngle();

        float ax = std::cos(angle) * distance + std::cos(aa) * p.getSize();
        float bx = std::cos(angle) * distance + std::cos(ab) * p.getSize();
        float cx = std::cos(angle) * distance + std::cos(ac) * p.getSize();

        float ay = std::sin(angle) * distance + std::sin(aa) * p.getSize();
        float by = std::sin(angle) * distance + std::sin(ab) * p.getSize();
        float cy = std::sin(angle) * distance + std::sin(ac) * p.getSize();

        vertices[a].position = sf::Vector2f(ax, ay) + p.getOrigin() + p.getOriginDelta();
        vertices[b].position = sf::Vector2f(bx, by) + p.getOrigin() + p.getOriginDelta();
        vertices[c].position = sf::Vector2f(cx, cy) + p.getOrigin() + p.getOriginDelta();
    } else if (active) {
        spawnParticle(p);
        //vertices[a].position = sf::Vector2f(origin.x, origin.y - p.getSize());
        //vertices[b].position = sf::Vector2f(origin.x + p.getSize(), origin.y + p.getSize());
        //vertices[c].position = sf::Vector2f(origin.x - p.getSize(), origin.y + p.getSize());
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
    p.spawn(Utility::random(Utility::pi(11, 12), Utility::pi(13, 12)), Utility::random(5, 15), Utility::random(0.05, 0.2), Utility::random(7, 12), invert, origin);
}

void ParticleEmitter2::end() {
	active = false;
}

bool ParticleEmitter2::isActive() const {
	return active;
}
