// JuegoSFML.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Personaje.h"
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
sf::FloatRect area;

Personaje* Protagonista = new Personaje(rutaProtagonista, 64,0, cEscaladoProtagonista, cEscaladoProtagonista);
Personaje* Profesor = new Personaje(cRutaProfesor, 700, 332, 3, -3);
Fondo* background = new Fondo(cRutaFondo);
#ifdef cRutaFondoLejano
Fondo* fondoLejano = new Fondo(cRutaFondoLejano,2.5f,2.5f);
#endif
Suelo* suelo = new Suelo(0.f, 1270,anchoPantalla*2, 10.f);

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
	
	lPersonajes.push_back(Profesor);
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
			//case sf::Event::Resized:
			//	area = sf::FloatRect(0, 0, event.size.width, event.size.height);
			//	window.setView(sf::View(area));
			//	break;
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
#ifdef cRutaFondoLejano
	window.draw(fondoLejano->getSprite());
#endif
	window.draw(background->getSprite());
	window.draw(Protagonista->getSprite());
	sf::View view(sf::FloatRect(fmax(52, (Protagonista->getX() - anchoPantalla / 2 * 0.35f)), fmin(1061, (Protagonista->getY() - anchoPantalla / 2 * 0.3f)), 319, 228));
	//sf::View view(sf::FloatRect(52 ,73,1600,1216));
	window.setView(view);
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
	window.setIcon(sfml_icon.width, sfml_icon.height, sfml_icon.pixel_data);
	window.setFramerateLimit(60);
}

void cierraJuego() {
	destruyePersonajes(lPersonajes);
	window.close();
}