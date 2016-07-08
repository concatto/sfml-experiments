/*
 * Animation.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "Animation.h"
#include <iostream>

Animation::Animation(std::vector<sf::IntRect> frames, int updateRate)
	: currentFrame(0), frames(frames), updateRate(updateRate), step(0) {
}

void Animation::update(sf::Sprite& target) {
	step++;
	if (step >= updateRate) {
		step = 0;
		currentFrame++;
		if (currentFrame >= frames.size()) currentFrame = 0;

		target.setTextureRect(frames[currentFrame]);
	}
}

void Animation::start(sf::Sprite& target) {
	step = 0;
	currentFrame = 0;
	target.setTextureRect(frames[currentFrame]);
}

void Animation::setUpdateRate(int updateRate) {
	this->updateRate = updateRate;
}

std::vector<sf::IntRect> Animation::generateFrames(int amount, sf::Vector2i size) {
	std::vector<sf::IntRect> frames;
	for (int i = 0; i < amount; i++) {
		frames.push_back(sf::IntRect(i * size.x, 0, size.x, size.y));
	}
	return frames;
}

