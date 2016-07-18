#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Updatable.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AnimationManager : public Updatable
{
    using Animation = std::vector<sf::IntRect>;

    sf::Sprite& target;
    std::vector<Animation> animations;
    unsigned int currentAnimation = 0;
    int updateRate = Normal;
    int step = 0;
    unsigned int currentFrame = 0;

public:
    enum Speed {Fast = 2, Normal = 5};

    AnimationManager(sf::Sprite& target);

    virtual void update() override;
    void updateTextureRect();
    static Animation generateFrames(sf::Vector2i size, int amount, sf::Vector2i startingPoint = sf::Vector2i(0, 0));
    void beginAnimation(unsigned int index);
    void loadAnimations(std::vector<Animation> animations);
    void setSpeed(Speed speed);
};

#endif // ANIMATIONMANAGER_H
