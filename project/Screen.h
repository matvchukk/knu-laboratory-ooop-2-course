#pragma once

constexpr unsigned char SQUARE = 16;
constexpr unsigned char HEIGHT = 21;
constexpr unsigned char WIDTH = 21;
constexpr unsigned short LIMIT = 10500;

constexpr unsigned char FRAMES = 6;
constexpr unsigned char SPEED = 4;

constexpr unsigned char ENEMY_SPEED = 1.5;
constexpr unsigned char USER_SPEED = 2;
constexpr unsigned short ENERGIZER = 512;

constexpr unsigned char SCARED = 4;
constexpr unsigned char VERY_SCARED = 3; // :0


constexpr unsigned short CHASE = 1024;
constexpr unsigned char ENEMY1_CHASE = 2;
constexpr unsigned char ENEMY2_CHASE = 1;
constexpr unsigned char ENEMY3_CHASE = 4;
constexpr unsigned short DISSIPATION = 512;

constexpr unsigned char DEFEAT = 15;
constexpr unsigned char SCREEN_RESIZE = 2;


constexpr unsigned short FLICKER = 64;

constexpr unsigned short DISSIPATION_LITTLE = 256;

struct Position
{
	int x, y;
	bool operator==(const Position& pos)
	{
		return (this->x == pos.x && this->y == pos.y);
	}
};

enum Square
{
	Wall,
	Exit,
	Empty,
	Energizer,
	Score
};
