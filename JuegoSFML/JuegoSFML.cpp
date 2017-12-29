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
#include <Box2D/Box2D.h>

void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lPersonajes, std::list< Fondo*  > lFondos);
void destruyePersonajes(std::list< Personaje * > lPersonajes);
void calculoTeclado();
void setPropiedadesVentana();
void cierraJuego();

void CreateGround(b2World& World, float X, float Y);

sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), tituloPantalla);
Personaje* Protagonista = new Personaje(rutaProtagonista, 0, 0, 2, 2);
Personaje* Profesor = new Personaje(rutaProfesor, 700, 332, 3, -3);
Fondo* background = new Fondo(rutaFondo2);

b2Vec2 Gravity(0.f, 9.8f);
b2World World(Gravity);

std::list< Personaje* > lPersonajes;
std::list< Fondo* > lFondos;

int main()
{
	setPropiedadesVentana();

	Protagonista->setFisicaSprite(World);
	lPersonajes.push_back(Profesor);
	lPersonajes.push_back(Protagonista);

	lFondos.push_back(background);
	
	CreateGround(World, 400.f, 415.f);

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
					Profesor->swapflip();
				}
			default:
				break;
			}
		}
	}
	return 0;
}

void CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SCALE, (0.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}


void cicloPintado(sf::RenderWindow& window, std::list< Personaje*  > lPersonajes, std::list< Fondo*  > lFondos) {
	World.Step(1 / 60.f, 8, 3);
	window.clear();
	Protagonista->calcularNuevaPosicion();
	window.draw(background->getSprite());
	window.draw(Protagonista->getSprite());
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