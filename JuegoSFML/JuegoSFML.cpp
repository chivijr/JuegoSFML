// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Personaje.h"
#include "Fondo.h"
#include "Mundo.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

Mundo cWorld;

void cicloPintado(sf::RenderWindow& window);
void destruyePersonajes(std::list< Personaje * > lPersonajes);
void calculoTeclado();
void setPropiedadesVentana();
void cierraJuego();

std::list< Personaje* > lPersonajes;
std::list< Fondo* > lFondos;

sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla,32), tituloPantalla, sf::Style::Default);
//Personaje* Protagonista = new Personaje(rutaProtagonista, 100, 400, 2, 2);
Personaje* Protagonista = new Personaje(cWorld, rutaProtagonista);
//Personaje* Profesor = new Personaje(&cWorld, rutaProfesor, 700, 332, 3, -3);
Personaje* Profesor = new Personaje(cWorld, rutaProfesor);
Fondo* background = new Fondo(rutaFondo2);


int main()
{
	setPropiedadesVentana();

	//lPersonajes.push_back(Profesor);
	//lPersonajes.push_back(Protagonista);

	//lFondos.push_back(background);

	while (window.isOpen())
	{
		//calculoTeclado();

		cicloPintado(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (logdebug) { std::cout << "Recogiendo Evento: " << event.type << "." << std::endl; };
			switch (event.type)
			{
			case sf::Event::Closed:
				cierraJuego();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					//Profesor->swapflip();
				}
			default:
				break;
			}
		}
	}
	return 0;
}

void cicloPintado(sf::RenderWindow& window) {
	window.clear();
	if (!lFondos.empty()) {
		window.draw((*lFondos.begin())->getSprite());
	}
	
	//std::list<Personaje*>::iterator it;

	/*for (it = ; it != lPersonajes.end(); ++it) {
		(*it)->calcularNuevaPosicion();
		window.draw((*it)->getSprite());
	};*/
	cWorld.getMundo()->Step(1 / 60.f, 8, 3);
	/*for (b2Body* BodyIterator = cWorld.getMundo()->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		if (BodyIterator->GetType() == b2_dynamicBody) {
			Protagonista->mover(BodyIterator->GetPosition().x, BodyIterator->GetPosition().y);
			window.draw(Protagonista->getSprite());
		}
	}*/
	window.draw(Protagonista->getSprite());
	window.draw(cWorld.getGround()->RECT);
	window.draw(cWorld.getLeftWall()->RECT);
	window.draw(cWorld.getRightWall()->RECT);
	window.display();
}

void destruyePersonajes(std::list< Personaje * > lPersonajes) {
	std::list<Personaje*>::iterator it;
	for (it = lPersonajes.begin(); it != lPersonajes.end(); ++it) {
		(*it)->~Personaje();
	}
}

void calculoTeclado() {
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Protagonista->setMoverArriba();
	} else {
		Protagonista->removeMoverArriba();
	};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		Protagonista->setMoverAbajo();
	} else {
		Protagonista->removeMoverAbajo();
	};*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		Protagonista->setMoverIzquierda();
	}
	else {
		Protagonista->removeMoverIzquierda();
	};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		Protagonista->setMoverDerecha();
	}
	else {
		Protagonista->removeMoverDerecha();
	};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { cierraJuego(); };
}

void setPropiedadesVentana() {
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
}

void cierraJuego() {
	destruyePersonajes(lPersonajes);
	window.close();
}