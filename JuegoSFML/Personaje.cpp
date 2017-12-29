#include "stdafx.h"
#include "Personaje.h"

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

void Personaje::calcularNuevaPosicion()
{
	mover(SCALE * Body->GetPosition().x, SCALE * Body->GetPosition().y);
	if (isMoviendoAbajo()) {
		//moverY(aceleracion);
	}
	if (isMoviendoArriba()) {
		//moverY(-aceleracion);
	}

	b2Vec2 vel = Body->GetLinearVelocity();
	if (isMoviendoDerecha()) {
		if (vel.x + aceleracion > cMaximaVelocidad) {
			velChange = cMaximaVelocidad;
		} else {
			velChange = vel.x + aceleracion;
		}
		impulse = Body->GetMass() * velChange; //disregard time factor
		Body->ApplyLinearImpulse(b2Vec2(impulse, 0), Body->GetWorldCenter(),true);
	} else if (vel.x > 0) {
		velChange = vel.x - cDeceleracion;
		impulse = Body->GetMass() * velChange; //disregard time factor
		Body->ApplyLinearImpulse(b2Vec2(0, 0), Body->GetWorldCenter(), true);
	}
	/*if (isMoviendoIzquierda()) {
		float desiredVel = 0;
		desiredVel = -cAceleracion;
		float velChange = desiredVel - vel.x;
		float impulse = Body->GetMass() * velChange; //disregard time factor
		Body->ApplyLinearImpulse(b2Vec2(impulse, 0), Body->GetWorldCenter(), true);
	}*/
}

void Personaje::setFisicaSprite(b2World& localWorld)
{
	BodyDef.position = b2Vec2(getX(),getY());
	BodyDef.type = b2_dynamicBody;
	Body = localWorld.CreateBody(&BodyDef);

	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	
	FixtureDef.density = 1.f;
	FixtureDef.friction = 5.0f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

/*void Personaje::saltar() {
	b2Vec2 vel = body->GetLinearVelocity();
	vel.y = 10;//upwards - don't change x velocity
	body->SetLinearVelocity(vel);
}*/

void Personaje::mover(int nuevax, int nuevay)
{
	sprite.setPosition(nuevax, nuevay);
	setX(nuevax);
	setY(nuevay);
}

void Personaje::moverX(int nuevax)
{
	sprite.move(nuevax, getY());
	setX(nuevax);
}

void Personaje::moverY(int nuevay)
{
	sprite.move(getX(), nuevay);
	setY(nuevay);
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
	}
	else {
		unflip();
		setFlipped(false);
	}
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
	//sprite.setOrigin(0,getAlto());
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

