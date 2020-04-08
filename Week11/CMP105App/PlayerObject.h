#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"
class PlayerObject : public GameObject
{
public:
	PlayerObject();
	~PlayerObject();

	virtual void handleInput(float dt) override;
	virtual void update(float dt) override;

	virtual void collisionResponse(GameObject* collider) override;


	void setSpeed(float s) { speed = s; };
	float getSpeed() { return speed; };

	void setView(sf::View* vw) { view = vw; };

protected:
	sf::View* view;

	float scale;
	sf::Vector2f gravity;
	sf::Vector2f jumpVector;
	bool isJumping;

	Animation* currentAni;
	Animation walkingAni;
	Animation swimingAni;
	Animation crouchingAni;


	float horizontalVelocity;
	bool isWalking;
	bool isCrouching;
	bool isFlipped;
	float speed;
};
