#include "stdafx.h"
#include "Fondo.h"


Fondo::Fondo(std::string Nombre)
{
	setTextura(Nombre);
	setSprite(texture);
	fitWindow();
}

Fondo::Fondo(std::string Nombre, float alto, float ancho)
{
	setTextura(Nombre);
	texture.setRepeated(true);
	setSprite(texture);
	escalarAbsoluto(alto,ancho);
}

Fondo::~Fondo()
{
}

sf::Texture Fondo::getTextura()
{
	return texture;
}

void Fondo::setTextura(std::string Nombre)
{
	if (!texture.loadFromFile(Nombre))
		exit;
	texture.setRepeated(true);
}

sf::Sprite Fondo::getSprite()
{
	return sprite;
}

void Fondo::setSprite(sf::Texture Fondo)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, anchoPantalla, altoPantalla));
}

void Fondo::escalarAbsoluto(float alto, float ancho) 
{
	sprite.setScale(alto, ancho);
}

void Fondo::fitWindow() {
	// Para adaptarlo perfectamente.
	//sprite.setScale(1 / sprite.getGlobalBounds().width * anchoPantalla, 1 / sprite.getGlobalBounds().height * altoPantalla);

	// Para adaptar el alto y que el ancho se vaya repitiendo.
	//sprite.setScale(1 / sprite.getGlobalBounds().width * anchoPantalla, 1 / sprite.getGlobalBounds().height * altoPantalla);
	sprite.setScale(1, 2);
}