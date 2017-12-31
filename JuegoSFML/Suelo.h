#pragma once
#include "Entidad.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Suelo : public Entidad
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

public:
	Suelo(float xinicial, float yinicial, float anchoInicial, float altoInicial);
	~Suelo();

	int getEntityType();

	void setFisicaSprite(b2World& localWorld);

	void setX(const int& nuevax);
	int& getX();
	void setY(const int& nuevay);
	int& getY();
	void setAncho(const int& nuevoancho);
	int& getAncho();
	void setAlto(const int& nuevoalto);
	int& getAlto();

	sf::Texture getTextura();
	bool setTextura(std::string Nombre);

	sf::Sprite getSprite();
	void setSprite(sf::Texture Personaje);

	sf::RectangleShape getShape();
};

