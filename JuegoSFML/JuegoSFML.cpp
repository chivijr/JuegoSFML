// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "textura.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "JuegoSFML");

	textura Protagonista("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/sprite/prota/airborne01.png");

	sf::Texture text = Protagonista.getTextura();
	text.loadFromFile("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/sprite/prota/airborne01.png");
	sf::Sprite sprite(text);

	while (window.isOpen())
	{
		window.clear();
		if (logdebug) {
			std::cout << "Antes de pintar." << std::endl;
		};
		window.draw(sprite);
		window.display();

		sf::Event event;
		// while there are pending events...
		while (window.pollEvent(event))
		{
			if (logdebug) { std::cout << "Recogiendo Evento: " << event.type << "." << std::endl;  };
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				if (logdebug) {
					std::cout << "Se ha presionado una tecla." << std::endl;
				}
				break;

			case sf::Event::MouseMoved:
				if (logdebug) {
					std::cout << "Se ha movido el raton." << std::endl;
				}
				// we don't process other types of events
			default:
				break;
			}
		}

	}

	return 0;
}