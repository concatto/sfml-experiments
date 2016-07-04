/*
 * Animation.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
	unsigned int currentFrame;
	std::vector<sf::IntRect> frames;
	int updateRate;
	int step;

public:
	enum UpdateSpeed {Fast = 2, Normal = 5, Slow = 10};
	Animation(std::vector<sf::IntRect> frames = std::vector<sf::IntRect>(), int updateRate = UpdateSpeed::Normal);

	void update(sf::Sprite& target);
	void start();
	void setUpdateRate(int updateRate);

	static std::vector<sf::IntRect> generateFrames(int amount, sf::Vector2i size);
};

#endif /* ANIMATION_H_ */
