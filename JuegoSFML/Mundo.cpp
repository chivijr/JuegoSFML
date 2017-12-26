#include "stdafx.h"
#include "Mundo.h"


Mundo::Mundo()
{
	b2Vec2 Gravity(0.f, 9.8f);
	mundo = new b2World(Gravity);
	//crearSuelo(0, 15);

	body ground;
	ground.DEF.position.Set(400.0f / 30, 600.0f / 30);
	//ground.DEF.type = b2_dynamicBody;
	ground.RECT = sf::RectangleShape(sf::Vector2f(8000, 25));//100-50? is size?
	ground.RECT.setOrigin(4000, 25);
	ground.RECT.setFillColor(sf::Color(200, 75, 20, 255));
	ground.SHAPE.SetAsBox(4000.0f / 30, 25.0f / 30);
	ground.BOD = mundo->CreateBody(&ground.DEF);
	ground.FIX.shape = &ground.SHAPE;
	ground.FIX.density = .7f;
	ground.FIX.friction = .9f;
	ground.BOD->CreateFixture(&ground.SHAPE, 1.0f);

	body leftWall;
	leftWall.DEF.position.Set(0.0f / 30, -300 / 30);
	//leftWall.DEF.type = b2_staticBody;
	leftWall.RECT = sf::RectangleShape(sf::Vector2f(25, 8000));//100-50? is size?
	leftWall.RECT.setOrigin(0, 4000);
	leftWall.RECT.setFillColor(sf::Color(200, 75, 200, 255));
	leftWall.SHAPE.SetAsBox(25.0f / 30, 4000.0f / 30);
	leftWall.BOD = mundo->CreateBody(&leftWall.DEF);
	leftWall.FIX.shape = &leftWall.SHAPE;
	leftWall.FIX.density = .7f;
	leftWall.FIX.friction = .9f;
	leftWall.BOD->CreateFixture(&leftWall.SHAPE, 1.0f);

	body rightWall;
	rightWall.DEF.position.Set(800.0f / 30, -300 / 30);
	//rightWall.DEF.type = b2_staticBody;
	rightWall.RECT = sf::RectangleShape(sf::Vector2f(25, 8000));//100-50? is size?
	rightWall.RECT.setOrigin(25, 4000);
	rightWall.RECT.setFillColor(sf::Color(100, 205, 20, 255));
	rightWall.SHAPE.SetAsBox(25.0f / 30, 4000.0f / 30);
	rightWall.BOD = mundo->CreateBody(&rightWall.DEF);
	rightWall.FIX.shape = &rightWall.SHAPE;
	rightWall.FIX.density = .7f;
	rightWall.FIX.friction = .9f;
	rightWall.BOD->CreateFixture(&rightWall.SHAPE, 1.0f);
}

Mundo::~Mundo()
{
}

void Mundo::crearSuelo(int x, int y) {
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = mundo->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(800 / 2, 600 / 2);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

b2World* Mundo::getMundo()
{
	return mundo;
}

body* Mundo::getGround()
{
	return& ground;
}

body* Mundo::getLeftWall()
{
	return& leftWall;
}

body* Mundo::getRightWall()
{
	return& rightWall;
}

