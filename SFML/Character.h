#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Character : public sf::Sprite {
private:
	enum Speed {Fast = 10, Normal = 2};

	static std::vector<Animation> animations;
	sf::Uint32 state;
	unsigned int animationIndex;
	bool animationPlaying;
	bool facingRight;
	int movementSpeed;
    sf::Vector2u sizeBounds;
    float force;

	void playAnimation(unsigned int index);

public:
    enum State {None = 0, Stand = 1, Walk = 2, Ground = 4};

	Character(const sf::Texture& texture, sf::Vector2u sizeBounds);

	void update();
	void accelerate();
	void slow();
	void moveLeft();
	void moveRight();
	void stand();
    void jump();
	bool isFacingRight() const;
	bool isMoving() const;
	sf::Vector2u getSizeBounds() const;
    sf::IntRect getBoundingBox() const;
	void draw(sf::RenderTarget& target);
    void notifyGroundDistance(int distance);
    void notifyCeilingDistance(int distance);

    void setState(State s);
    void unsetState(State s);
    bool getState(State s) const;
};

#endif /* CHARACTER_H_ */
