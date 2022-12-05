#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "User.h"
#include "Render.h"

std::array<std::array<Square, HEIGHT>, WIDTH> mapRendering(User& user, std::array<Position, 4>& enemy, const std::array<std::string, HEIGHT>& outline)
{
	std::array<std::array<Square, HEIGHT>, WIDTH> result{};

	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			result[j][i] = Square::Empty;

			if (outline[i][j] == '#')	
				result[j][i] = Square::Wall;
			else if (outline[i][j] == '=')	
				result[j][i] = Square::Exit;
			else if (outline[i][j] == '.')	
				result[j][i] = Square::Score;
			else if (outline[i][j] == 'P')
				user.setPosition(SQUARE * j, SQUARE * i);
			else if (outline[i][j] == 'o')
				result[j][i] = Square::Energizer;
			else if (outline[i][j] == '0')
			{
				enemy[0].x = SQUARE * j;
				enemy[0].y = SQUARE * i;
			}
			else if (outline[i][j] == '1')
			{
				enemy[1].x = SQUARE * j;
				enemy[1].y = SQUARE * i;
			}
			else if (outline[i][j] == '2')
			{
				enemy[2].x = SQUARE * j;
				enemy[2].y = SQUARE * i;
			}
			else if (outline[i][j] == '3')
			{
				enemy[3].x = SQUARE * j;
				enemy[3].y = SQUARE * i;
			}
		}
	}

	return result;
}