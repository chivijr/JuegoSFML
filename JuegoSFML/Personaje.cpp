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

void Personaje::escalar(float nuevoAlto, float nuevoAncho)
{
	sprite.scale(nuevoAlto, nuevoAncho);
}

Personaje::Personaje()
{
	x = 0;
	y = 0;
	aceleracion = cAceleracion;
	texture.~Texture();
}

Personaje::Personaje(std::string Nombre)
{
	x = 0;
	y = 0;
	aceleracion = cAceleracion;
	setTextura(Nombre);
	setSprite(texture);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	escalar(2, 2);
}

Personaje::Personaje(std::string Nombre, int posx, int posy)
{
	x = posx;
	y = posx;
	aceleracion = cAceleracion;
	setTextura(Nombre);
	setSprite(texture);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	escalar(2, 2);
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
}

 bool Personaje::setX(const int& nuevax)
{
	 x = nuevax;
	 return true;
}

 bool Personaje::setY(const int& nuevay)
 {
	 y = nuevay;
	 return true;
 }

int& Personaje::getX() 
{
	return x;
}

int& Personaje::getY()
{
	return y;
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

