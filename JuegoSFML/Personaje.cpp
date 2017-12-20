#include "stdafx.h"
#include "Personaje.h"


Personaje::Personaje()
{
	x = 0;
	y = 0;
	texture.~Texture();
}

Personaje::Personaje(std::string Nombre)
{
	x = 0;
	y = 0;
	setTextura(Nombre);
	setSprite(texture);
}

Personaje::Personaje(std::string Nombre, int posx, int posy)
{
	x = posx;
	y = posx;
	setTextura(Nombre);
	setSprite(texture);
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