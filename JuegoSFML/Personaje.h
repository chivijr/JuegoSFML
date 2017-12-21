#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Personaje
{
private:
	int x, y;
	int aceleracion;
	sf::Texture texture;
	sf::Sprite sprite;
	bool moverArriba;
	bool moverAbajo;
	bool moverDerecha;
	bool moverIzquierda;
public:
	void calcularNuevaPosicion();
	// Métodos
	void mover(int nuevax, int nuevay);
	void escalar(float nuevoAlto, float nuevoAncho);

	// Constructores
	Personaje();
	Personaje(std::string Nombre);
	Personaje(std::string Nombre, int posx, int posy);

	// Getter & Setter
	sf::Texture getTextura();
	bool setTextura(std::string Nombre);

	sf::Sprite getSprite();
	void setSprite(sf::Texture Personaje);

	bool setX(const int& x);
	int& getX();

	bool setY(const int& y);
	int& getY();

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