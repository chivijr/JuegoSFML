#pragma once
#ifndef FONDO_H
#define FONDO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"

class Fondo {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	// Métodos
	void escalarAbsoluto(float alto, float ancho);
	void fitWindow();
	void fitWindow(int anchoPantallalocal, int altoPantallalocal);

	// Constructor y destructor
	Fondo(std::string Nombre);
	Fondo(std::string Nombre, float alto, float ancho);
	~Fondo();

	// Getter & Setter
	sf::Texture getTextura();
	void setTextura(std::string Nombre);

	sf::Sprite getSprite();
	void setSprite(sf::Texture Personaje);
};

#endif


