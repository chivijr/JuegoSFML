#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Mundo.h"
#include "Constantes.h"


struct body
{
	b2BodyDef DEF;
	b2PolygonShape SHAPE;
	b2FixtureDef FIX;
	b2Body * BOD;
	sf::RectangleShape RECT;
};

class Mundo
{
private:
	b2World* mundo;

	body ground;
	body leftWall;
	body rightWall;

public:
	// Constructor y destructor
	Mundo();
	~Mundo();
	
	// Métodos del mundo
	void crearSuelo(int x, int y);

	// Getter & Setter
	b2World* getMundo();
	body* getGround();
	body* getLeftWall();
	body* getRightWall();
};