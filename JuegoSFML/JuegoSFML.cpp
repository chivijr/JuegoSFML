// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Personaje.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>

void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lProtagonistas) {
	window.clear();
	std::list<Personaje*>::iterator it;
	for (it = lProtagonistas.begin(); it != lProtagonistas.end(); ++it) {
		window.draw((*it)->getSprite());
	};
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "JuegoSFML");

	std::list< Personaje* > lPersonajes;

	Personaje Protagonista("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/sprite/prota/walk01.png");
	Personaje Protagonista2("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/sprite/prota/walk02.png",10,10);

	lPersonajes.push_back(&Protagonista);
	lPersonajes.push_back(&Protagonista2);

	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Protagonista.setMoverArriba();
		}
		else {
			Protagonista.removeMoverArriba();
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Protagonista.setMoverAbajo();
		}
		else {
			Protagonista.removeMoverAbajo();
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Protagonista.setMoverIzquierda();
		}
		else {
			Protagonista.removeMoverIzquierda();
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Protagonista.setMoverDerecha();
		}
		else {
			Protagonista.removeMoverDerecha();
		};
		cicloPintado(window ,lPersonajes);

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
				Protagonista.~Personaje();
				Protagonista2.~Personaje();
				window.close();
				break;

			// key pressed
			case sf::Event::KeyPressed:
				break;
			
				// key released
			/*case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					Protagonista.removeMoverArriba();
					break;
				case sf::Keyboard::Down:
					Protagonista.removeMoverAbajo();
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
				break;*/
			case sf::Event::MouseMoved:

				// we don't process other types of events
			default:
				break;
			}
		}

	}

	return 0;
}