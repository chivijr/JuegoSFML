#pragma once
#ifndef Profesor_H
#define Profesor_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Box2D/Box2D.h>
#include "Constantes.h"
#include "Entidad.h"


class Profesor : public Entidad
{
private:
	// Gráficos
	int posx, posy;
	int ancho, alto;
	sf::Texture texture;
	sf::Sprite animatedSprite;
	sf::RectangleShape rectangulo;

	// Física
	b2BodyDef BodyDef;
	b2Body* Body;
	b2PolygonShape Shape;
	b2FixtureDef FixtureDef;
	b2Vec2 momentum;
	float aceleracion;
	float deceleracion;
	b2Vec2 velocidad;
	int m_contacting;

	// Estado	
	bool moverArriba;
	bool moverAbajo;
	bool moverDerecha;
	bool moverIzquierda;
	bool saltando;
	bool flipped;


public:
	// Métodos del Profesor
	void saltar();

	// Métodos propiedades
	void mover(int nuevax, int nuevay);
	void moverX(int nuevax);
	void moverY(int nuevay);
	void escalar(float nuevoAlto, float nuevoAncho);
	void flip();
	void unflip();
	void swapflip();
	void calcularNuevaPosicion();
	void setFisicaSprite(b2World& localWorld);

	// Constructores
	Profesor(std::string Nombre);
	Profesor(std::string Nombre, int posxinicial, int posyinicial);
	Profesor(std::string Nombre, int posxinicial, int posyinicial, int anchoinicial, int altoincial);

	// Getter & Setter
	sf::Texture getTextura();
	bool setTextura(std::string Nombre);

	sf::Sprite getSprite();
	void setSprite(sf::Texture Profesor);

	sf::RectangleShape getShape();

	void setX(const int& nuevax);
	int& getX();

	void setY(const int& nuevay);
	int& getY();

	void setAncho(const int& nuevoancho);
	int& getAncho();

	void setAlto(const int& nuevoalto);
	int& getAlto();

	void setFlipped(const bool& flipeado);
	bool& getFlipped();

	b2Body* getBody();

	b2Vec2 getLinearVelocity();

	void startContact();
	void endContact();

	int getEntityType();

	void setMoverArriba();
	void setMoverAbajo();
	void setMoverDerecha();
	void setMoverIzquierda();
	void setSaltando();

	void removeMoverArriba();
	void removeMoverAbajo();
	void removeMoverDerecha();
	void removeMoverIzquierda();
	void removeSaltando();

	bool isMoviendoArriba();
	bool isMoviendoAbajo();
	bool isMoviendoIzquierda();
	bool isMoviendoDerecha();
	bool isSaltando();

	// Destructor
	~Profesor();
};
#endif