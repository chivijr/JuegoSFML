#pragma once
#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Personaje
{
private:
	int posx, posy;
	int ancho, alto;
	int aceleracion;
	sf::Texture texture;
	sf::Sprite sprite;
	bool moverArriba;
	bool moverAbajo;
	bool moverDerecha;
	bool moverIzquierda;
	bool flipped;
public:
	void calcularNuevaPosicion();
	// Métodos
	void mover(int nuevax, int nuevay);
	void moverX(int nuevax);
	void moverY(int nuevay);
	void escalar(float nuevoAlto, float nuevoAncho);
	void flip();
	void unflip();
	void swapflip();

	// Constructores
	//Personaje();
	Personaje(std::string Nombre);
	Personaje(std::string Nombre, int posxinicial, int posyinicial);
	Personaje(std::string Nombre, int posxinicial, int posyinicial, int anchoinicial, int altoincial);

	// Getter & Setter
	sf::Texture getTextura();
	bool setTextura(std::string Nombre);

	sf::Sprite getSprite();
	void setSprite(sf::Texture Personaje);

	void setX(const int& nuevax);
	int& getX();

	void setY(const int& nuevay);
	int& getY();

	void setAncho(const int& nuevoancho);
	int& getAncho();

	void setAlto(const int& nuevoalto);
	int& getAlto();

	void setFlipped(const bool& flipeado);
	bool& getFlipped();
	
	void setMoverArriba();
	void setMoverAbajo();
	void setMoverDerecha();
	void setMoverIzquierda();

	void removeMoverArriba();
	void removeMoverAbajo();
	void removeMoverDerecha();
	void removeMoverIzquierda();

	bool isMoviendoArriba();
	bool isMoviendoAbajo();
	bool isMoviendoIzquierda();
	bool isMoviendoDerecha();

	// Destructor
	~Personaje();
};
#endif