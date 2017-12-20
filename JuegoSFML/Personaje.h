#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Personaje
{
private:
	int x, y;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	// Constructores
	Personaje();
	Personaje(std::string Nombre);
	Personaje(std::string Nombre, int posx, int posy);

	// Getter & Setter
	sf::Texture getTextura();
	bool setTextura(std::string Nombre);

	sf::Sprite getSprite();
	void setSprite(sf::Texture Personaje);

	bool setX(int &x);
	int getX();

	bool setY(int &y);
	int getY();

	// Destructor
	~Personaje();
};