#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Map.h"
#include "Render.h"

//#include <iostream>
#include <array>

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(SQUARE * WIDTH * SCREEN_RESIZE, (SQUARE * HEIGHT) * SCREEN_RESIZE), "PacMan", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, SQUARE * WIDTH, SQUARE * HEIGHT)));

	
	std::array<std::string, HEIGHT> outline =
	{
		" ################### ",
		" #        #        # ",
		"                     ",
		"                     ",
		"                     ",
		"                     ",
		" #### ### # ### #### ",
		"    # #       # #    ",
		"##### # ## ##   #####",
		"         # #         ",
		"##### # ##### # #####",
		"    # #       # #    ",
		" ##### #####    #### ",
		"                     ",
		"                     ",
		" #                 # ",
		"                     ",
		"                     ",
		"                     ",
		"                     ",
		" ################### "
	};

	std::array<std::array<Square, HEIGHT>, WIDTH> map{};
	map = mapRendering(outline);

	unsigned time = 0;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		float elapsed = clock.getElapsedTime().asMicroseconds(); 
		clock.restart();
		time += elapsed;
		//std::cout << time << std::endl;
		while (LIMIT <= time)
		{
			time -= LIMIT;

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
				}
				}
			}

			if (LIMIT > time)
			{
				window.clear();
				mapPrinting(map, window);
				window.display();
			}
		}
	}
	return 0;
}