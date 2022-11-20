#include <SFML/Graphics.hpp>
#include "Screen.h"

//#include <iostream>

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(SQUARE * WIDTH * SCREEN_RESIZE, (SQUARE * HEIGHT) * SCREEN_RESIZE), "PacMan", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, SQUARE * WIDTH, SQUARE * HEIGHT)));

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
		}
	}
	return 0;
}