#include "stdafx.h"
#include "textura.h"


textura::textura()
{
	x = 0;
	y = 0;
	texture.~Texture();
}

textura::textura(std::string Nombre)
{
	x = 0;
	y = 0;
	if (!texture.loadFromFile(Nombre))
	{
		std::cout << "Error al asignar la imagen: " << Nombre << std::endl;
	}
}

textura::textura(std::string Nombre, int posx, int posy)
{
	x = posx;
	y = posx;
	if (!texture.loadFromFile(Nombre))
	{
		std::cout << "Error al asignar la imagen: " << Nombre << std::endl;
	}
}

sf::Texture textura::getTextura()
{
	return sf::Texture();
}

bool textura::setTextura(sf::Texture &text)
{
	texture = &text;
}


textura::~textura()
{
}