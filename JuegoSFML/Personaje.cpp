#include "stdafx.h"
#include "Personaje.h"
#include "Constantes.h"

Personaje::Personaje(Mundo& World, std::string Nombre)
{
	posx = 0;
	posy = 0;
	aceleracion = cAceleracion;
	setFisicaSprite(World);
	setTextura(Nombre);
	setSprite(texture);
	setAncho(sprite.getGlobalBounds().width);
	setAlto(sprite.getGlobalBounds().height);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	escalar(2, 2);
	flipped = false;
}

Personaje::Personaje(Mundo& World, std::string Nombre, int posxinicial, int posyinicial)
{
	mover(posxinicial, posyinicial);
	setX(posxinicial);
	setY(posyinicial);
	aceleracion = cAceleracion;
	setFisicaSprite(World);
	setTextura(Nombre);
	setSprite(texture);
	setAncho(sprite.getGlobalBounds().width);
	setAlto(sprite.getGlobalBounds().height);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	flipped = false;
}

Personaje::Personaje(Mundo& World, std::string Nombre, int posxinicial, int posyinicial, int anchoinicial, int altoinicial)
{
	mover(posxinicial, posyinicial);
	setX(posxinicial);
	setY(posyinicial);
	aceleracion = cAceleracion;
	setFisicaSprite(World);
	setTextura(Nombre);
	setSprite(texture);
	escalar(altoinicial, anchoinicial);
	setAncho(sprite.getGlobalBounds().width);
	setAlto(sprite.getGlobalBounds().height);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	flipped = false;
}

void Personaje::setFisicaSprite(Mundo& World) {
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(getX() / SCALE, getY() / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.getMundo()->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}
void Personaje::calcularNuevaPosicion()
{
	if (isMoviendoAbajo()) {
		mover(0, aceleracion);
	}
	if (isMoviendoArriba()) {
		mover(0, -aceleracion);
	}
	if (isMoviendoDerecha()) {
		mover(aceleracion, 0);
	}
	if (isMoviendoIzquierda()) {
		mover(-aceleracion, 0);
	}
}

/*void Personaje::saltar() {
	b2Vec2 vel = body->GetLinearVelocity();
	vel.y = 10;//upwards - don't change x velocity
	body->SetLinearVelocity(vel);
}*/

void Personaje::mover(int nuevax, int nuevay)
{
	sprite.move(nuevax, nuevay);
}

void Personaje::moverX(int nuevax)
{
	sprite.move(nuevax, posy);
}

void Personaje::moverY(int nuevay)
{
	sprite.move(posx, nuevay);
}

void Personaje::escalar(float nuevoAlto, float nuevoAncho)
{
	sprite.scale(nuevoAlto, nuevoAncho);
}

void Personaje::flip() {
	sprite.setTextureRect(sf::IntRect(ancho, 0, -ancho, alto));
	//sprite.setTextureRect(sf::IntRect(0, alto, ancho, -alto));
	flipped = true;
}

void Personaje::unflip() {
	sprite.setTextureRect(sf::IntRect(0, 0, ancho, alto));
	flipped = false;
}

void Personaje::swapflip() {
	if (!flipped) {
		flip();
		setFlipped(true);
	}
	else {
		unflip();
		setFlipped(false);
	}
}


sf::Texture Personaje::getTextura()
{
	return texture;
}

bool Personaje::setTextura(std::string Nombre)
{
	return texture.loadFromFile(Nombre);
}

sf::Sprite Personaje::getSprite()
{
	return sprite;
}

void Personaje::setSprite(sf::Texture Personaje)
{
	sprite.setTexture(texture);
	//sprite.setOrigin(0,getAlto());
}

Personaje::~Personaje()
{
	std::cout << "Destruyendo Personaje." << std::endl;
}

void Personaje::setX(const int& nuevax)
{
	posx = nuevax;
}

void Personaje::setY(const int& nuevay)
{
	posy = nuevay;
}

int& Personaje::getX()
{
	return posx;
}

int& Personaje::getY()
{
	return posy;
}

void Personaje::setAncho(const int & nuevoancho)
{
	ancho = nuevoancho;
}

int & Personaje::getAncho()
{
	return ancho;
}

void Personaje::setAlto(const int & nuevoalto)
{
	alto = nuevoalto;
}

int & Personaje::getAlto()
{
	return alto;
}

void Personaje::setFlipped(const bool & flipeado)
{
	flipped = flipeado;
}

bool & Personaje::getFlipped()
{
	return flipped;
}

void Personaje::setMoverArriba()
{
	moverArriba = true;
}
void Personaje::setMoverAbajo()
{
	moverAbajo = true;
}
void Personaje::setMoverDerecha()
{
	moverDerecha = true;
}
void Personaje::setMoverIzquierda()
{
	moverIzquierda = true;
}
void Personaje::removeMoverArriba()
{
	moverArriba = false;
}
void Personaje::removeMoverAbajo()
{
	moverAbajo = false;
}
void Personaje::removeMoverDerecha()
{
	moverDerecha = false;
}
void Personaje::removeMoverIzquierda()
{
	moverIzquierda = false;
}
bool Personaje::isMoviendoArriba()
{
	return moverArriba;
}
bool Personaje::isMoviendoAbajo()
{
	return moverAbajo;
}
bool Personaje::isMoviendoIzquierda()
{
	return moverIzquierda;
}
bool Personaje::isMoviendoDerecha()
{
	return moverDerecha;
}

