#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class textura
{
private:
	int x, y;
	sf::Texture texture;
public:
	// Constructores
	textura();
	textura(std::string Nombre);
	textura(std::string Nombre, int posx, int posy);

	// Getter & Setter
	sf::Texture getTextura();
	bool setTextura(std::string Nombre);

	bool setX(int &x);
	int getX();

	bool setY(int &y);
	int getY();

	// Destructor
	~textura();
};