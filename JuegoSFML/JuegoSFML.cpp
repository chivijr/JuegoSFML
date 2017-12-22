// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Personaje.h"
#include "Fondo.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), "JuegoSFML");
Personaje* Protagonista = new Personaje(rutaProtagonista);
Personaje* Profesor = new Personaje(rutaProfesor, 200, 100, 3, 3);
Fondo* back = new Fondo("C:/Users/Chivijr/source/repos/JuegoSFMLSolucion/Debug/recursos/working-title-assets/untitled folder/exterior-parallaxBG1.png");

void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lPersonajes, std::list< Fondo*  > lFondos) {
	window.clear();
	std::list<Personaje*>::iterator it;
	window.draw((*lFondos.begin())->getSprite());
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

void calculoTeclado() {
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
}

int main()
{
	
	std::list< Personaje* > lPersonajes;
	std::list< Fondo* > lFondos;

	lPersonajes.push_back(Profesor);
	lPersonajes.push_back(Protagonista);

	lFondos.push_back(back);
	
	while (window.isOpen())
	{
		calculoTeclado();

		cicloPintado(window ,lPersonajes,lFondos);

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