#pragma once

class Enemy
{
	Position home;
	Position exit;
	Position pos;
	Position enemyPurpose;

	bool regime;
	bool isExit;

	unsigned char motion;
	unsigned char fearMeasure;
	unsigned char fearT;
	unsigned short motionT;

	unsigned char id;	

public:
	Enemy(unsigned char id);

	void setPosition(int x, int y);
	Position getPosition();

	float purposeLength(unsigned char direction);
	void setPurpose(unsigned char user, const Position& enemyPosCurr, const Position& enemyPos);

	void setRegime();
	bool userCollision(const Position& user);

	void draw(bool flash, sf::RenderWindow& window);
	void resetting(const Position& home, const Position& door);
	void update(unsigned char level, std::array<std::array<Square, HEIGHT>, WIDTH>& map, User& user, Enemy& enemyCurr);
};


class EnemyTools
{
	std::array<Enemy, 4> ghosts;
	unsigned char wave;
	unsigned short waveT;

public:
	EnemyTools();

	void draw(bool flash, sf::RenderWindow& window);
	void resetting(size_t level, const std::array<Position, 4>& enemy);
	void update(size_t level, std::array<std::array<Square, HEIGHT>, WIDTH>& map, User& user);
};