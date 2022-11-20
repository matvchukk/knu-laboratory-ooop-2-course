#include <SFML/Graphics.hpp>

#include <array>
#include "Screen.h"
#include "Map.h"


void mapPrinting(const std::array<std::array<Square, HEIGHT>, WIDTH>& rendered, sf::RenderWindow& myWindow)
{
	sf::RectangleShape mapSquare(sf::Vector2f(SQUARE, SQUARE));
	for (char i = 0; i < WIDTH; i++)
	{
		for (char j = 0; j < HEIGHT; j++)
		{
			mapSquare.setPosition(SQUARE * i, SQUARE * j);
			switch (rendered[i][j])
			{
			case Square::Wall:
			{
				mapSquare.setFillColor(sf::Color(93, 136, 255));

				myWindow.draw(mapSquare);
				break;
			}
			}
		}
	}
}