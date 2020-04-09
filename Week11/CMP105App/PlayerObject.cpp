#include "PlayerObject.h"

PlayerObject::PlayerObject()
{

	view = nullptr;
	// initialise gravity value (gravity 9.8, 200 scale, 200 p/s this will need to be uniform)
	scale = 200.0f;
	gravity = sf::Vector2f(0, 9.8f) * scale;
	jumpVector = sf::Vector2f(0, -3.5f) * scale;
	isJumping = false;


	//initalise walking animation
	walkingAni.addFrame(sf::IntRect(0, 0, 15, 21));
	walkingAni.addFrame(sf::IntRect(15, 0, 15, 21));
	walkingAni.addFrame(sf::IntRect(30, 0, 15, 21));
	walkingAni.addFrame(sf::IntRect(45, 0, 15, 21));
	walkingAni.setFrameSpeed(0.1f);

	swimingAni.addFrame(sf::IntRect(0, 21, 16, 20));
	swimingAni.addFrame(sf::IntRect(16, 21, 16, 20));
	swimingAni.addFrame(sf::IntRect(32, 21, 16, 20));
	swimingAni.setFrameSpeed(0.1f);

	crouchingAni.addFrame(sf::IntRect(0, 41, 16, 20));
	crouchingAni.addFrame(sf::IntRect(16, 41, 16, 20));
	crouchingAni.setFrameSpeed(0.1f);


	currentAni = &walkingAni;
	setTextureRect(currentAni->getCurrentFrame());

	horizontalVelocity = 0;
	isWalking = false;
	isCrouching = false;
	isFlipped = false;
	speed = 180;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::handleInput(float dt)
{
	// Jump, check if already jumping
	if (input->isKeyDown(sf::Keyboard::W))
	{
		if (!isJumping)
		{
			audio->playSoundbyName("jump");
			velocity = jumpVector;
			isJumping = true;
		}
	}

	//get direction from input
	if (input->isKeyDown(sf::Keyboard().A))
	{
		isWalking = true;
		isFlipped = true;
		horizontalVelocity = -1;
	}
	else if (input->isKeyDown(sf::Keyboard().D))
	{
		isWalking = true;
		isFlipped = false;
		horizontalVelocity = 1;
	}
	else
	{
		isWalking = false;
		horizontalVelocity = 0;
	}

	velocity.x = horizontalVelocity * speed;

	//start / stop crouching from input
	if (input->isKeyDown(sf::Keyboard().LControl))
	{
		isCrouching = true;
	}
	else
	{
		isCrouching = false;
		crouchingAni.reset();
	}
}

void PlayerObject::update(float dt)
{
	// Apply gravity force, increasing velocity
	// Move shape by new velocity
	sf::Vector2f pos = velocity * dt + 0.5f * gravity * dt * dt; //ut+ 1/2at^2
	velocity += gravity * dt; // v = u + at  note the += is not =
	setPosition(getPosition() + pos);

	// Check for collision with bottom of window
	if (getPosition().y >= (view->getSize().y - getSize().y))
	{
		setPosition(getPosition().x, (view->getSize().y - getSize().y));
		velocity = sf::Vector2f(0, 0);
		isJumping = false;
	}

	//find correct animation
	if (isJumping)
	{
		setCollisionBox(0, 0, 32, 40);
		setSize(sf::Vector2f(32, 40));
		currentAni = &swimingAni;
	}
	else if (isCrouching)
	{
		if (audio->getSound("up")->getStatus() != sf::SoundSource::Status::Playing)
		{
			audio->playSoundbyName("up");
		}
		setCollisionBox(0, 0, 32, 40);
		setSize(sf::Vector2f(32, 40));
		currentAni = &crouchingAni;
	}
	else
	{
		setCollisionBox(0, 0, 30, 42);
		setSize(sf::Vector2f(30, 42));
		currentAni = &walkingAni;
	}

	//animate if in motion
	if (isWalking)
	{

		//Animate
		currentAni->animate(dt);
	}

	//set current frame and direction
	currentAni->setFlipped(isFlipped);
	setTextureRect(currentAni->getCurrentFrame());
}

void PlayerObject::collisionResponse(GameObject* collider)
{
	//sf::FloatRect colliderCollisionBox = collider->getCollisionBox();
	float xDiff = getPosition().x - collider->getPosition().x;
	float yDiff = getPosition().y - collider->getPosition().y;

	if (abs(xDiff) - (0.5f * (getSize().x + collider->getSize().x)) > abs(yDiff) - (0.5f * (getSize().y + collider->getSize().y)))
	{
		//x-axis collision
		if (xDiff < 0)
		{
			//collision from left
			setPosition(collider->getPosition().x - getSize().x - 0.1, getPosition().y);
		}
		else
		{
			//collision from right
			setPosition(collider->getPosition().x + collider->getSize().x + 0.1, getPosition().y);
		}

	}
	else
	{
		//y-axis collision
		if (yDiff < 0)
		{
			//collision from above
			if (velocity.y > 0)
			{
				isJumping = false;
				velocity.y = 0;
				setPosition(getPosition().x, collider->getPosition().y - getSize().y);
			}
		}
		else
		{
			//collision from below
			velocity.y = -(velocity.y / 3);
			setPosition(getPosition().x, collider->getPosition().y + collider->getSize().y);
		}
	}
}
