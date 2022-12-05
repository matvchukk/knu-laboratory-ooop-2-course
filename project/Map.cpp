#include <SFML/Graphics.hpp>

#include <cmath>
#include <array>
#include "Screen.h"
#include "Map.h"


void print(const std::array<std::array<Square, HEIGHT>, WIDTH>& outline, sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sf::RectangleShape mapSquare(sf::Vector2f(SQUARE, SQUARE));
	sf::CircleShape score;
	sf::CircleShape speed;
	
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			sprite.setPosition(static_cast<float>(SQUARE * i), static_cast<float>(SQUARE * j));
			if (outline[i][j] == Square::Wall)
			{
				mapSquare.setFillColor(sf::Color(93, 136, 255));
				mapSquare.setPosition(static_cast<float>(SQUARE * i), static_cast<float>(SQUARE * j));
				window.draw(mapSquare);
			}
			else if (outline[i][j] == Square::Energizer)
			{
				speed.setRadius(SQUARE / 4);
				speed.setPosition(SQUARE * i + (SQUARE / 2 - speed.getRadius()), SQUARE * j + (SQUARE / 2 - speed.getRadius()));
				speed.setFillColor(sf::Color(255, 183, 170));
				window.draw(speed);
			}
			else if (outline[i][j] == Square::Score)
			{
				score.setRadius(SQUARE / 8);
				score.setPosition(SQUARE * i + (SQUARE / 2 - score.getRadius()), SQUARE * j + (SQUARE / 2 - score.getRadius()));
				score.setFillColor(sf::Color(255, 183, 170));
				window.draw(score);
			}
		}
	}
}

bool collision(int x, int y, std::array<std::array<Square, HEIGHT>, WIDTH>& map, bool score, bool exit)
{
	float xCurr = x/static_cast<float>(SQUARE);
	float yCurr = y/static_cast<float>(SQUARE);

	bool result = 0;
	for (size_t i = 0; i < 4; i++)
	{
		int x = 0;
		int y = 0;

		if (i == 0)
		{
			x = static_cast<int>(floor(xCurr));
			y = static_cast<int>(floor(yCurr));
		}
		else if (i == 1)
		{
			x = static_cast<int>(ceil(xCurr));
			y = static_cast<int>(floor(yCurr));
		}
		else if (i == 2)
		{
			x = static_cast<int>(floor(xCurr));
			y = static_cast<int>(ceil(yCurr));
		}
		else if (i == 3)
		{
			x = static_cast<int>(ceil(xCurr));
			y = static_cast<int>(ceil(yCurr));
		}

		if (HEIGHT > y && WIDTH > x && x >= 0 && y >= 0)
		{
			if (!score) 
			{
				if (Square::Wall == map[x][y])
				{
					result = 1;
				}
				else if (Square::Exit == map[x][y] && (!exit))
				{
					result = 1;
				}
			}
			else 
			{
				if (Square::Energizer == map[x][y])
				{
					result = 1;
					map[x][y] = Square::Empty;
				}
				else if (Square::Score == map[x][y])
				{
					map[x][y] = Square::Empty;
				}
			}
		}
	}

	return result;
}

