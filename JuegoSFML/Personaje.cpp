#include "stdafx.h"
#include "Personaje.h"
#include "Constantes.h"

void Personaje::calcularNuevaPosicion()
{
	if (isMoviendoAbajo()) { 
		mover(0, aceleracion);
	}
	if (isMoviendoArriba()) { 
		mover(0, -aceleracion); 
	}
	if (isMoviendoDerecha()) { 
		mover(aceleracion,0); 
	}
	if (isMoviendoIzquierda()) { 
		mover(-aceleracion,0); 
	}
}

void Personaje::mover(int nuevax, int nuevay)
{
	sprite.move(nuevax, nuevay);
}

void Personaje::moverX(int nuevax)
{
	sprite.move(nuevax,posy);
}

void Personaje::moverY(int nuevay)
{
	sprite.move(posx,nuevay);
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
	} else {
		unflip();
		setFlipped(false);
	}
}

Personaje::Personaje(std::string Nombre)
{
	posx = 0;
	posy = 0;
	aceleracion = cAceleracion;
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

Personaje::Personaje(std::string Nombre, int posxinicial, int posyinicial)
{
	mover(posxinicial, posyinicial);
	setX(posxinicial);
	setY(posyinicial);
	aceleracion = cAceleracion;
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

Personaje::Personaje(std::string Nombre, int posxinicial, int posyinicial, int anchoinicial, int altoinicial)
{
	mover(posxinicial, posyinicial);
	setX(posxinicial);
	setY(posyinicial);
	aceleracion = cAceleracion;
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

