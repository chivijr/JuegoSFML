// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "Personaje.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>

void cicloPintado(sf::RenderWindow& window, Personaje Protagonista) {
	window.clear();
	Protagonista.calcularNuevaPosicion();
	window.draw(Protagonista.getSprite());
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "JuegoSFML");

	Personaje Protagonista("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/sprite/prota/walk01.png");

	while (window.isOpen())
	{
		cicloPintado(window ,Protagonista);

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
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					Protagonista.setMoverArriba();
					break;
				case sf::Keyboard::Down:
					Protagonista.setMoverAbajo();
					break;
				case sf::Keyboard::Left:
					Protagonista.setMoverIzquierda();
					break;
				case sf::Keyboard::Right:
					Protagonista.setMoverDerecha();
					break;
				default:
					break;
				}
				break;
			
				// key released
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					Protagonista.removeMoverArriba();
					break;
				case sf::Keyboard::Down:
					Protagonista.removeMoverAbajo();
					break;
				case sf::Keyboard::Left:
					Protagonista.removeMoverIzquierda();
					break;
				case sf::Keyboard::Right:
					Protagonista.removeMoverDerecha();
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseMoved:

				// we don't process other types of events
			default:
				break;
			}
		}

	}

	return 0;
}