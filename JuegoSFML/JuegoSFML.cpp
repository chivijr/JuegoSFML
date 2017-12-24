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
void CreateGround(b2World& World, float X, float Y);
void CreateBox(b2World& World, int MouseX, int MouseY);

sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), tituloPantalla);
Personaje* Protagonista = new Personaje(rutaProtagonista,100, 350,2,2);
Personaje* Profesor = new Personaje(rutaProfesor, 700, 350, 3, -3);
Fondo* back = new Fondo(rutaFondo);

b2Vec2 Gravity(0.f, 9.8f);
b2World World(Gravity);
 
int main()
{

	CreateGround(World, 400.0f, 500.f);

	window.setVerticalSyncEnabled(true);
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
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					destruyePersonajes(lPersonajes);
					window.close();
					break;
				}
				break;

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
	Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void CreateBox(b2World& World, int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}


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