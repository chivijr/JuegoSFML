// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Personaje.h"
#include "Profesor.h"
#include "Fondo.h"
#include "Constantes.h"
#include "MyContactListener.h"
#include "Suelo.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lPersonajes, std::list< Fondo*  > lFondos);
void destruyePersonajes(std::list< Personaje * > lPersonajes);
void calculoTeclado();
void setPropiedadesVentana();
void cierraJuego();

sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), tituloPantalla);
Personaje* Protagonista = new Personaje(rutaProtagonista, 26,0, 2, 2);
Profesor* Profe = new Profesor(rutaProfesor, 700, 332, 3, -3);
Fondo* background = new Fondo(rutaFondo2);
Suelo* suelo = new Suelo(0.f, 522.f,anchoPantalla*2, 10.f);

b2Vec2 Gravity(0.f, cGravity);
b2World World(Gravity);
MyContactListener myContactListenerInstance;

std::list< Personaje* > lPersonajes;
std::list< Fondo* > lFondos;

int main()
{
	
	// Propiedades de la ventana de SFML
	setPropiedadesVentana();

	// Le incluimos la información al mundo de box2D
	World.SetContactListener(&myContactListenerInstance);
	Protagonista->setFisicaSprite(World);
	suelo->setFisicaSprite(World);
	World.DrawDebugData();
	
	//lPersonajes.push_back(Profe);
	lPersonajes.push_back(Protagonista);

	lFondos.push_back(background);

	while (window.isOpen())
	{
		World.Step(1 / 60.f, 8, 3);
		calculoTeclado();

		cicloPintado(window, lPersonajes, lFondos);

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
					Protagonista->saltar();
				}
			default:
				break;
			}
		}
	}
	return 0;
}

void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lPersonajes, std::list< Fondo*  > lFondos) {
	World.Step(1 / 60.f, 8, 3);
	window.clear();
	Protagonista->calcularNuevaPosicion();
	window.draw(background->getSprite());
	window.draw(Profe->getSprite());
	//window.draw(Protagonista->getSprite());
	window.draw(Protagonista->getAnimatedSprite());
	//window.draw(suelo->getShape());
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