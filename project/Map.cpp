#include <SFML/Graphics.hpp>

#include <array>
#include "Screen.h"
#include "Map.h"


void mapPrinting(const std::array<std::array<Square, HEIGHT>, WIDTH>& rendered, sf::RenderWindow& i_window)
{
	sf::RectangleShape cell_shape(sf::Vector2f(SQUARE, SQUARE));
	for (char i = 0; i < WIDTH; i++)
	{
		for (char j = 0; j < HEIGHT; j++)
		{
			cell_shape.setPosition(SQUARE * i, SQUARE * j);
			switch (rendered[i][j])
			{
			case Square::Wall:
			{
				cell_shape.setFillColor(sf::Color(93, 136, 255));

				i_window.draw(cell_shape);

				break;
			}
			}
		}
	}
}