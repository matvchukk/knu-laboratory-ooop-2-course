#include <array>
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Map.h"
#include "User.h"
#include "Enemy.h"
#include "Render.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(SQUARE * WIDTH * SCREEN_RESIZE, (SQUARE * HEIGHT) * SCREEN_RESIZE), "Pac-Man!!", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, SQUARE * WIDTH, SQUARE * HEIGHT)));

	EnemyTools newEnemies;
	User newUser;
	bool win = 0;
	size_t level = 0;

	srand(time(NULL));

	std::array<std::string, HEIGHT> outline =
	{
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};

	std::array<std::array<Square, HEIGHT>, WIDTH> map{};
	std::array<Position, 4> enemiesPosition;

	map = mapRendering(newUser, enemiesPosition, outline);
	newEnemies.resetting(level, enemiesPosition);

	unsigned time = 0;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		float elapsed = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time += elapsed;

		while (LIMIT <= time)
		{
			time -= LIMIT;

			if ((!win) && (!newUser.getIsDead()))
			{
				win = 1;
				newUser.update(level, map);
				newEnemies.update(level, map, newUser);

				for (const std::array<Square, HEIGHT>& column : map)
				{
					for (const Square& cell : column)
					{
						if (Square::Score == cell)
						{
							win = 0;
							break;
						}
					}

					if (!win)
					{
						break;
					}
				}

				if (win)
				{
					newUser.motionTimer(0);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				win = 0;

				if (!newUser.getIsDead())
				{
					level++;
				}
				else
				{
					level = 0;
				}

				map = mapRendering(newUser, enemiesPosition, outline);
				newEnemies.resetting(level, enemiesPosition);
				newUser.resetting();
			}

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)	window.close();
			}

			if (LIMIT > time)
			{
				window.clear();

				if (!win && !newUser.getIsDead())
				{
					print(map, window);
					newEnemies.draw(FLICKER >= newUser.scareTimer(), window);
				}

				newUser.draw(win, window);
				window.display();
			}
		}
	}

	return 0;
}

