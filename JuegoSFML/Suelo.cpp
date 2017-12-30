#include "stdafx.h"
#include "Suelo.h"

Suelo::Suelo(float xinicial, float yinicial, float anchoIncicial, float altoIncicial) {
	this->posx = xinicial;
	this->posy = yinicial;
	this->ancho = anchoIncicial;
	this->alto = altoIncicial;
	sf::RectangleShape rectangle(sf::Vector2f(anchoIncicial, altoIncicial));
	this->rectangulo = rectangle;
	this->rectangulo.setPosition(this->posx, this->posy);
}

Suelo::~Suelo() {
}

int Suelo::getEntityType() {
	return SUELO;
}

void Suelo::setFisicaSprite(b2World& localWorld)
{
	float prueba = this->posx + (this->posx / 2);
	BodyDef.position = b2Vec2(anchoPantalla/2, this->posy/2);
	BodyDef.type = b2_staticBody;
	Body = localWorld.CreateBody(&BodyDef);
	Shape.SetAsBox((this->ancho) / 2, (0.f / 2) / 2);
	FixtureDef.density = 1.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	Body->SetUserData(Body);
 }

void Suelo::setX(const int& nuevax)				{ posx = nuevax; }
void Suelo::setY(const int& nuevay)				{ posy = nuevay; }
int& Suelo::getX()								{ return posx; }
int& Suelo::getY()								{ return posy; }

bool Suelo::setTextura(std::string Nombre)		{ return texture.loadFromFile(Nombre); }
void Suelo::setSprite(sf::Texture Personaje)	{ sprite.setTexture(texture); }
sf::Texture Suelo::getTextura()					{ return texture; }
sf::Sprite Suelo::getSprite()					{ return sprite; }

sf::RectangleShape Suelo::getShape() { return rectangulo; }

