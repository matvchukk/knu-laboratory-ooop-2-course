#pragma once

class User
{
	Position pos;

	unsigned char motion;
	unsigned short motionT;
	unsigned short scareT;

	bool dead;

public:
	User();

	void setPosition(int x, int y);
	Position getPosition();

	bool getIsDead();
	void setIsDead(bool isDead);

	unsigned char getMotion();

	unsigned short scareTimer();
	void motionTimer(unsigned short motionT);
	
	void resetting();	
	void update(size_t level, std::array<std::array<Square, HEIGHT>, WIDTH>& map);
	void draw(bool win, sf::RenderWindow& window);
};