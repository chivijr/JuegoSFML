// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Personaje.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lPersonajes) {
	window.clear();
	std::list<Personaje*>::iterator it;
	for (it = lPersonajes.begin(); it != lPersonajes.end(); ++it) {
		(*it)->calcularNuevaPosicion();
		window.draw((*it)->getSprite());
	};
	window.display();
}

void destruyePersonajes(std::list< Personaje * > lPersonajes) {
	std::list<Personaje*>::iterator it;
	for (it = lPersonajes.begin(); it != lPersonajes.end(); ++it) {
		(*it)->~Personaje();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "JuegoSFML");

	std::list< Personaje* > lPersonajes;

	Personaje* Protagonista = new Personaje("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/sprite/prota/walk01.png");
	Personaje* Profesor = new Personaje("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/maestro/idle01.png",200,100);

	std::cout << Profesor->getAlto() << std::endl;
	std::cout << Profesor->getAncho() << std::endl;

	//Profesor->escalar(-1, 1);

	lPersonajes.push_back(Profesor);
	lPersonajes.push_back(Protagonista);
	
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Protagonista->setMoverArriba();
		}
		else {
			Protagonista->removeMoverArriba();
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Protagonista->setMoverAbajo();
		}
		else {
			Protagonista->removeMoverAbajo();
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Protagonista->setMoverIzquierda();
		}
		else {
			Protagonista->removeMoverIzquierda();
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Protagonista->setMoverDerecha();
		}
		else {
			Protagonista->removeMoverDerecha();
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
				destruyePersonajes(lPersonajes);
				window.close();
				break;

			// key pressed
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					Profesor->swapflip();
				}
				break;

			default:
				break;
			}
		}

	}

	return 0;
}