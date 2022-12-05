#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "User.h"
#include "Enemy.h"
#include "Map.h"

Enemy::Enemy(unsigned char id) :
	id(id)
{}

bool Enemy::userCollision(const Position& user)
{
	if (pos.x > user.x - SQUARE && pos.x < SQUARE + user.x)
	{
		if (pos.y > user.y - SQUARE && pos.y < SQUARE + user.y)
		{
			return 1;
		}
	}

	return 0;
}
void Enemy::update(unsigned char level, std::array<std::array<Square, HEIGHT>, WIDTH>& map, User& user, Enemy& enemyCurr)
{
	bool move = 0;
	unsigned char ways = 0;
	unsigned char speed = ENEMY_SPEED;

	std::array<bool, 4> vecCollision{};

	if (!fearMeasure && user.scareTimer() == ENERGIZER_DURATION / pow(2, level))
	{
		fearT = VERY_SCARED;
		fearMeasure = 1;
	}
	else if (fearMeasure && !user.scareTimer())
	{
		fearMeasure = 0;
	}

	if (fearMeasure == 2 && (pos.x % SCARED == 0) && (pos.y % SCARED == 0))
	{
		speed = SCARED;
	}
	setPurpose(user.getMotion(), enemyCurr.getPosition(), user.getPosition());
	vecCollision[0] = collision(speed + pos.x, pos.y, map, 0, isExit);
	vecCollision[1] = collision(pos.x, pos.y - speed, map, 0, isExit);
	vecCollision[2] = collision(pos.x - speed, pos.y, map, 0, isExit);
	vecCollision[3] = collision(pos.x, speed + pos.y, map, 0, isExit);

	if (fearMeasure != 1)
	{
		unsigned char rePurpose = 4;
		move = 1;

		for (unsigned char i = 0; i < 4; i++)
		{
			if (i == (2 + motion) % 4)
			{
				continue;
			}
			else if (!vecCollision[i])
			{
				if (rePurpose == 4)
				{
					rePurpose = i;
				}
				ways++;

				if (purposeLength(i) < purposeLength(rePurpose))
				{
					rePurpose = i;
				}
			}
		}

		if (ways > 1)
		{
			motion = rePurpose;
		}
		else
		{
			if (rePurpose == 4)
			{
				motion = (2 + motion) % 4;
			}
			else
			{
				motion = rePurpose;
			}
		}
	}
	else
	{
		unsigned char randPurpose = rand() % 4;

		if (!fearT)
		{
			move = 1;
			fearT = VERY_SCARED;

			for (unsigned char i = 0; i < 4; i++)
			{
				if (i == (2 + motion) % 4)
				{
					continue;
				}
				else if (!vecCollision[i])
				{
					ways++;
				}
			}

			if (ways > 0)
			{
				while (vecCollision[randPurpose] == 1 || randPurpose == (2 + motion) % 4)
				{
					randPurpose = rand() % 4;
				}

				motion = randPurpose;
			}
			else
			{
				motion = (2 + motion) % 4;
			}
		}
		else
		{
			fearT--;
		}
	}

	if (move)
	{
		if (motion == 0)		pos.x += speed;
		else if (motion == 1)	pos.y -= speed;
		else if (motion == 2)	pos.x -= speed;
		else if (motion == 3)	pos.y += speed;

		if (pos.x <= -SQUARE)
		{
			pos.x = SQUARE * WIDTH - speed;
		}
		else if (SQUARE * WIDTH <= pos.x)
		{
			pos.x = speed - SQUARE;
		}
	}

	if (userCollision(user.getPosition()))
	{
		if (!fearMeasure) 
		{
			user.setIsDead(1);
		}
		else 
		{
			enemyPurpose = home;
			isExit = 1;
			fearMeasure = 2;
		}
	}
}


float Enemy::purposeLength(unsigned char direction)
{
	short x = pos.x;
	short y = pos.y;

	if (direction == 0)			x += ENEMY_SPEED;
	else if (direction == 1)	y -= ENEMY_SPEED;
	else if (direction == 2)	x -= ENEMY_SPEED;
	else if (direction == 3)	y += ENEMY_SPEED;


	return static_cast<float>(sqrt(pow(x - enemyPurpose.x, 2) + pow(y - enemyPurpose.y, 2)));
}

void Enemy::draw(bool flash, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(motionT / static_cast<float>(SPEED)));

	sf::CircleShape enemyCircle(SQUARE / 2);
	sf::RectangleShape enemySquare(sf::Vector2f(2 * enemyCircle.getRadius(), enemyCircle.getRadius()));
	

	enemyCircle.setPosition(pos.x, pos.y);
	enemySquare.setPosition(pos.x, pos.y + SQUARE/2);	
	
	if (!fearMeasure)
	{
		switch (id)
		{
		case 0:
		{
			enemyCircle.setFillColor(sf::Color(255, 0, 0));
			enemySquare.setFillColor(sf::Color(255, 0, 0));

			break;
		}
		case 1:
		{
			enemyCircle.setFillColor(sf::Color(255, 192, 255));
			enemySquare.setFillColor(sf::Color(255, 192, 255));

			break;
		}
		case 2:
		{
			enemyCircle.setFillColor(sf::Color(0, 265, 255));
			enemySquare.setFillColor(sf::Color(0, 265, 255));

			break;
		}
		case 3:
		{
			enemyCircle.setFillColor(sf::Color(245, 182, 85));
			enemySquare.setFillColor(sf::Color(245, 182, 85));

			break;
		}
		}

		enemyCircle.setTextureRect(sf::IntRect(SQUARE * motion, SQUARE, SQUARE, SQUARE));
		enemySquare.setTextureRect(sf::IntRect(SQUARE * motion, SQUARE, SQUARE, SQUARE));

		i_window.draw(enemyCircle);
		i_window.draw(enemySquare);
	}
	else if (fearMeasure == 1)
	{
		enemySquare.setFillColor(sf::Color(136, 326, 255));
		enemySquare.setTextureRect(sf::IntRect(4 * SQUARE, SQUARE, SQUARE, SQUARE));
		enemyCircle.setFillColor(sf::Color(136, 326, 255));
		enemyCircle.setTextureRect(sf::IntRect(4 * SQUARE, SQUARE, SQUARE, SQUARE));

		if (flash && frame % 2 == 0)
		{
			enemySquare.setFillColor(sf::Color(22, 255, 25));
			enemyCircle.setFillColor(sf::Color(22, 255, 25));
		}
		else
		{
			enemySquare.setFillColor(sf::Color(45, 136, 45));
			enemyCircle.setFillColor(sf::Color(45, 136, 45));
		}

		i_window.draw(enemySquare);
		i_window.draw(enemyCircle);
	}
	else
	{
		enemySquare.setTextureRect(sf::IntRect(SQUARE * motion, 2 * SQUARE, SQUARE, SQUARE));
		enemyCircle.setTextureRect(sf::IntRect(SQUARE * motion, 2 * SQUARE, SQUARE, SQUARE));

		enemySquare.setFillColor(sf::Color(90, 86, 155));
		enemyCircle.setFillColor(sf::Color(90, 86, 155));
	}

	i_window.draw(enemySquare);
	i_window.draw(enemyCircle);

	motionT = (1 + motionT) % (FRAMES * SPEED);
}

void Enemy::resetting(const Position& myHome, const Position& door)
{
	regime = 0;
	isExit = 0 < id;

	motion = 0;
	fearMeasure = 0;
	fearT = 0;

	motionT = 0;

	home = myHome;
	exit = door;
	enemyPurpose = door;
}

void Enemy::setPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Enemy::setRegime()
{
	regime = 1 - regime;
}



void Enemy::setPurpose(unsigned char user, const Position& enemyPosCurr, const Position& enemyPos)
{
	if (isExit) 
	{
		if (pos == enemyPurpose)
		{
			if (exit == enemyPurpose) 
			{
				isExit = 0; 
			}
			else if (home == enemyPurpose) 
			{
				fearMeasure = 0; 
				enemyPurpose = exit; 
			}
		}
	}
	else
	{
		if (!regime) 
		{
			if (id == 0)		enemyPurpose = { SQUARE * (WIDTH - 1), 0 };
			else if (id == 1)	enemyPurpose = { 0, 0 };
			else if (id == 2)	enemyPurpose = { SQUARE * (WIDTH - 1), SQUARE * (HEIGHT - 1) };
			else if (id == 3)	enemyPurpose = { 0, SQUARE * (HEIGHT - 1) };
			
		}
		else 
		{
			if (id == 0)		
				enemyPurpose = enemyPos;
			else if (id == 1)
			{
				enemyPurpose = enemyPos;

				if (user == 0)	enemyPurpose.x += SQUARE * ENEMY1_CHASE;
				else if (user == 1)	enemyPurpose.y -= SQUARE * ENEMY1_CHASE;
				else if (user == 2)	enemyPurpose.x -= SQUARE * ENEMY1_CHASE;
				else if (user == 3)	enemyPurpose.y += SQUARE * ENEMY1_CHASE;

			}
			else if (id == 2)	
			{
				enemyPurpose = enemyPos;

				if (user == 0)	enemyPurpose.x += SQUARE * ENEMY2_CHASE;
				else if (user == 1)	enemyPurpose.y -= SQUARE * ENEMY2_CHASE;
				else if (user == 2)	enemyPurpose.x -= SQUARE * ENEMY2_CHASE;
				else if (user == 3)	enemyPurpose.y += SQUARE * ENEMY2_CHASE;

				enemyPurpose.x += enemyPurpose.x - enemyPosCurr.x;
				enemyPurpose.y += enemyPurpose.y - enemyPosCurr.y;

			}
			else if (id == 3)
			{
				if (SQUARE * ENEMY3_CHASE <= sqrt(pow(pos.x - enemyPos.x, 2) + pow(pos.y - enemyPos.y, 2)))
				{
					enemyPurpose = enemyPos;
				}
				else
				{
					enemyPurpose = { 0, SQUARE * (HEIGHT - 1) };
				}
			}
		}
	}
}

Position Enemy::getPosition()
{
	return pos;
}

EnemyTools::EnemyTools() :
	wave(0),
	waveT(LONG_SCATTER_DURATION),
	ghosts({ Enemy(0), Enemy(1), Enemy(2), Enemy(3) })
{

}

void EnemyTools::draw(bool flash, sf::RenderWindow& window)
{
	for (Enemy& ghost : ghosts)
	{
		ghost.draw(flash, window);
	}
}

void EnemyTools::resetting(size_t level, const std::array<Position, 4>& enemy)
{
	wave = 0;
	waveT = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, level));

	for (size_t i = 0; i < 4; i++)
	{
		ghosts[i].setPosition(enemy[i].x, enemy[i].y);
	}

	for (Enemy& ghost : ghosts)
	{
		ghost.resetting(ghosts[2].getPosition(), ghosts[0].getPosition());
	}
}

void EnemyTools::update(size_t level, std::array<std::array<Square, HEIGHT>, WIDTH>& map, User& user)
{
	if (user.scareTimer() == 0)
	{
		if (!waveT)
		{
			if (wave < 7)
			{
				for (Enemy& ghost : ghosts)
				{
					ghost.setRegime();
				}
				wave++;
			}

			if (wave % 2 == 1)
			{
				waveT = CHASE_DURATION;
			}
			else if (wave == 2)
			{
				waveT = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, level));
			}
			else
			{
				waveT = static_cast<unsigned short>(SHORT_SCATTER_DURATION / pow(2, level));
			}
		}
		else
		{
			waveT--;
		}
	}

	for (Enemy& ghost : ghosts)
	{
		ghost.update(level, map, user, ghosts[0]);
	}
}
