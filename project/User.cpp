#include <SFML/Graphics.hpp>

#include <array>
#include <cmath>

#include "Screen.h"
#include "Map.h"
#include "User.h"


User::User() :
	motion(0),
	scareT(0),
	dead(0),
	pos({ 0, 0 })
{}

bool User::getIsDead()
{
	return dead;
}

unsigned char User::getMotion()
{
	return motion;
}

unsigned short User::scareTimer()
{
	return scareT;
}

void User::draw(bool win, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(motionT / static_cast<float>(SPEED)));

	sf::CircleShape pacman(SQUARE / 2);
	pacman.setFillColor(sf::Color(245, 245, 0));
	pacman.setPosition(pos.x, pos.y);

	i_window.draw(pacman);

	if (dead || win)
	{
		if (motionT < DEFEAT * SPEED)
		{
			motionT++;
		}
	}
	else
	{
		i_window.draw(pacman);
		motionT = (1 + motionT) % (FRAMES * SPEED);
	}
}

void User::resetting()
{
	motion = 0;
	motionT = 0;
	scareT = 0;
	dead = 0;
}

void User::motionTimer(unsigned short motionTimer)
{
	motionT = motionTimer;
}

void User::setIsDead(bool isDead)
{
	dead = isDead;

	if (isDead)
	{
		motionT = 0;
	}
}

void User::setPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void User::update(size_t level, std::array<std::array<Square, HEIGHT>, WIDTH>& map)
{
	std::array<bool, 4> vecCollision{};
	vecCollision[0] = collision(USER_SPEED + pos.x, pos.y, map, 0, 0);
	vecCollision[1] = collision(pos.x, pos.y - USER_SPEED, map, 0, 0);
	vecCollision[2] = collision(pos.x - USER_SPEED, pos.y, map, 0, 0);
	vecCollision[3] = collision(pos.x, USER_SPEED + pos.y, map, 0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!vecCollision[0]) 
		{
			motion = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!vecCollision[1])
		{
			motion = 1;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!vecCollision[2])
		{
			motion = 2;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!vecCollision[3])
		{
			motion = 3;
		}
	}

	if (!vecCollision[motion])
	{
		if (motion == 0)		pos.x += USER_SPEED;
		else if (motion == 1)	pos.y -= USER_SPEED;
		else if (motion == 2)	pos.x -= USER_SPEED;
		else if (motion == 3)	pos.y += USER_SPEED;
	}

	if (pos.x <= -SQUARE)
	{
		pos.x = SQUARE * WIDTH - USER_SPEED;
	}
	else if (pos.x >= SQUARE * WIDTH)
	{
		pos.x = USER_SPEED - SQUARE;
	}

	if (collision(pos.x, pos.y, map, 1, 0))
	{
		scareT = static_cast<unsigned short>(ENERGIZER_DURATION / pow(3, level));
	}
	else
	{
		scareT = std::max(0, scareT - 1);
	}
}

Position User::getPosition()
{
	return pos;
}
