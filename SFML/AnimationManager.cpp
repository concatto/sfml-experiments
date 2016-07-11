#include "AnimationManager.h"
#include <iostream>

AnimationManager::AnimationManager(sf::Sprite &target) : target(target)
{

}

void AnimationManager::update()
{
    step++;
    if (step >= updateRate) {
        step = 0;
        currentFrame++;

        if (currentFrame >= animations[currentAnimation].size()) {
            currentFrame = 0;
        }

        updateTextureRect();
    }
}

void AnimationManager::loadAnimations(std::vector<Animation> animations) {
    this->animations = animations;
}

void AnimationManager::beginAnimation(unsigned int index) {
    currentAnimation = index;
    currentFrame = 0;
    step = 0;
    updateTextureRect();
}

void AnimationManager::setSpeed(Speed speed) {
    updateRate = speed;
}

void AnimationManager::updateTextureRect()
{
    target.setTextureRect(animations[currentAnimation][currentFrame]);
}

AnimationManager::Animation AnimationManager::generateFrames(sf::Vector2i size, int amount, sf::Vector2i startingPoint) {
    Animation frames;

    for (int i = 0; i < amount; i++) {
        frames.push_back(sf::IntRect(i * size.x + startingPoint.x, startingPoint.y, size.x, size.y));
    }

    return frames;
}
