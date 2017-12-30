#include "stdafx.h"
#include "Personaje.h"

Personaje::Personaje(std::string Nombre) :
	momentum(0,0),
	velocidad(4,0)
{
	posx = 0;
	posy = 0;
	aceleracion = cAceleracion;
	deceleracion = cDeceleracion;
	m_contacting = 0;
	setTextura(Nombre);
	setSprite(texture);
	setAncho(sprite.getGlobalBounds().width);
	setAlto(sprite.getGlobalBounds().height);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	removeSaltando();
	escalar(2, 2);
	flipped = false;
}

Personaje::Personaje(std::string Nombre, int posxinicial, int posyinicial) :
	momentum(0, 0),
	velocidad(4, 0)
{
	mover(posxinicial, posyinicial);
	setX(posxinicial);
	setY(posyinicial);
	aceleracion = cAceleracion;
	deceleracion = cDeceleracion;
	m_contacting = 0;
	setTextura(Nombre);
	setSprite(texture);
	setAncho(sprite.getGlobalBounds().width);
	setAlto(sprite.getGlobalBounds().height);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	removeSaltando();
	flipped = false;
}

Personaje::Personaje(std::string Nombre, int posxinicial, int posyinicial, int anchoinicial, int altoinicial) :
	momentum(0, 0),
	velocidad(4, 0)
{
	mover(posxinicial, posyinicial);
	setX(posxinicial);
	setY(posyinicial);
	aceleracion = cAceleracion;
	deceleracion = cDeceleracion;
	m_contacting = 0;
	setTextura(Nombre);
	setSprite(texture);
	escalar(altoinicial, anchoinicial);
	setAncho(sprite.getGlobalBounds().width);
	setAlto(sprite.getGlobalBounds().height);
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	removeSaltando();
	flipped = false;
}

void Personaje::calcularNuevaPosicion()
{
	float desiredVelocity = 0;
	if (isMoviendoAbajo()) {
		//moverY(aceleracion);
	}
	if (isMoviendoArriba()) {
		//moverY(-aceleracion);
	}
	
	// Movimiento izquierda y derecha
	momentum.x = Body->GetLinearVelocity().x;
	// Si no se est� moviendo o si est� pulsando los dos lados a la vez.
	if ((isMoviendoDerecha() && isMoviendoIzquierda()) || (!isMoviendoDerecha() && !isMoviendoIzquierda())) {
		desiredVelocity = 0;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange, 0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	} else if (isMoviendoDerecha()) {
		//unflip();
		desiredVelocity = aceleracion;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange,0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	} else if  (isMoviendoIzquierda()) {
		//flip();
		desiredVelocity = -aceleracion;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange, 0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	} 

	/*if (isSaltando()) {
		Body->ApplyForce(b2Vec2(0, 500), Body->GetWorldCenter(),true);
	}*/

	if (m_contacting > 0) {

	}
	mover(SCALE * Body->GetPosition().x, SCALE * Body->GetPosition().y);
	std::cout << "Y: " << Body->GetPosition().y << std::endl;
}

void Personaje::setFisicaSprite(b2World& localWorld) {
	BodyDef.position = b2Vec2(this->posx,this->posy);
	BodyDef.type = b2_dynamicBody;
	Body = localWorld.CreateBody(&BodyDef);

	Shape.SetAsBox(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	
	FixtureDef.density = 1.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	Body->SetUserData(this);
}

void Personaje::saltar() {
	if (!isSaltando()) {
		setSaltando();
	}
	b2Vec2 pos = Body->GetPosition();
	this->Body->ApplyLinearImpulse(b2Vec2(50, 50), Body->GetPosition(), true);
}

void Personaje::mover(int nuevax, int nuevay) {
	sprite.setPosition(nuevax, nuevay);
	setX(nuevax);
	setY(nuevay);
}

void Personaje::moverX(int nuevax) {
	sprite.move(nuevax, getY());
	setX(nuevax);
}

void Personaje::moverY(int nuevay) {
	sprite.move(getX(), nuevay);
	setY(nuevay);
}

void Personaje::escalar(float nuevoAlto, float nuevoAncho) {
	sprite.scale(nuevoAlto, nuevoAncho);
}

void Personaje::flip() {
	//sprite.setTextureRect(sf::IntRect(ancho, 0, -ancho, alto));
	flipped = true;
}

void Personaje::unflip() {
	//sprite.setTextureRect(sf::IntRect(0, 0, ancho, alto));
	flipped = false;
}

void Personaje::swapflip() {
	if (!flipped) {
		flip();
		setFlipped(true);
	} else {
		unflip();
		setFlipped(false);
	}
}

sf::Texture Personaje::getTextura() { return texture; }
bool Personaje::setTextura(std::string Nombre) { return texture.loadFromFile(Nombre); }

sf::Sprite Personaje::getSprite() {	return sprite; }
void Personaje::setSprite(sf::Texture Personaje) { sprite.setTexture(texture); }

Personaje::~Personaje() {
	std::cout << "Destruyendo Personaje." << std::endl;
}

void Personaje::setX(const int& nuevax) { posx = nuevax; }
void Personaje::setY(const int& nuevay) { posy = nuevay; }
int& Personaje::getX() { return posx; }
int& Personaje::getY() { return posy; }

void Personaje::setAncho(const int & nuevoancho) { ancho = nuevoancho; }
int & Personaje::getAncho() { return ancho; }

void Personaje::setAlto(const int & nuevoalto) { alto = nuevoalto; }
int & Personaje::getAlto() { return alto; }

void Personaje::setFlipped(const bool & flipeado) {	flipped = flipeado; }
bool & Personaje::getFlipped() { return flipped; }

b2Body* Personaje::getBody() { return Body; }
sf::RectangleShape Personaje::getShape() { return rectangulo; }
b2Vec2 Personaje::getLinearVelocity() {	return Body->GetLinearVelocity(); }

void Personaje::startContact() { m_contacting++; }
void Personaje::endContact() { m_contacting--; }

int Personaje::getEntityType() { return PERSONAJE; }

void Personaje::setMoverArriba() { moverArriba = true; }
void Personaje::setMoverAbajo() { moverAbajo = true; }
void Personaje::setMoverDerecha() {	moverDerecha = true; }
void Personaje::setMoverIzquierda() { moverIzquierda = true; }
void Personaje::setSaltando() {	saltando = true; }
void Personaje::removeMoverArriba() { moverArriba = false; }
void Personaje::removeMoverAbajo() { moverAbajo = false; }
void Personaje::removeMoverDerecha() { moverDerecha = false; }
void Personaje::removeMoverIzquierda() { moverIzquierda = false; }
void Personaje::removeSaltando() { saltando = false; }
bool Personaje::isMoviendoArriba() { return moverArriba; }
bool Personaje::isMoviendoAbajo() { return moverAbajo; }
bool Personaje::isMoviendoDerecha() { return moverDerecha; }
bool Personaje::isMoviendoIzquierda() { return moverIzquierda; }
bool Personaje::isSaltando() { return saltando; }