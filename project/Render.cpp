#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Render.h"

std::array<std::array<Square, HEIGHT>, WIDTH> mapRendering(const std::array<std::string, HEIGHT>& outline)
{
	std::array<std::array<Square, HEIGHT>, WIDTH> print{};

	for (char i = 0; i < HEIGHT; i++)
	{
		for (char j = 0; j < WIDTH; j++)
		{
			switch (outline[i][j])
			{
			case ' ':
			{
				print[j][i] = Square::Empty;

				break;
			}
			case '#':
			{
				print[j][i] = Square::Wall;

				break;
			}
			case '=':
			{
				print[j][i] = Square::Exit;

				break;
			}

			}
		}
	}

	return print;
}