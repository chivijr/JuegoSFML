#include "stdafx.h"
#include "Profesor.h"

Profesor::Profesor(std::string Nombre) :
	momentum(0, 0),
	velocidad(4, 0)
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

Profesor::Profesor(std::string Nombre, int posxinicial, int posyinicial) :
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

Profesor::Profesor(std::string Nombre, int posxinicial, int posyinicial, int anchoinicial, int altoinicial) :
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
	sprite.setOrigin({ animatedSprite.getLocalBounds().width / 2, 0 });
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	removeSaltando();
	flipped = false;
}

void Profesor::calcularNuevaPosicion()
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
	// Si no se está moviendo o si está pulsando los dos lados a la vez.
	if ((isMoviendoDerecha() && isMoviendoIzquierda()) || (!isMoviendoDerecha() && !isMoviendoIzquierda())) {
		desiredVelocity = 0;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange, 0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	}
	else if (isMoviendoDerecha()) {
		unflip();
		desiredVelocity = aceleracion;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange, 0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	}
	else if (isMoviendoIzquierda()) {
		flip();
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
}

void Profesor::setFisicaSprite(b2World& localWorld) {
	BodyDef.position = b2Vec2(this->posx, this->posy);
	BodyDef.type = b2_dynamicBody;
	Body = localWorld.CreateBody(&BodyDef);

	Shape.SetAsBox(sprite.getGlobalBounds().width / 2, animatedSprite.getGlobalBounds().height / 2);

	FixtureDef.density = 1.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	Body->SetUserData(this);
}

void Profesor::saltar() {
	if (!isSaltando()) {
		setSaltando();
	}
	b2Vec2 pos = Body->GetPosition();
	this->Body->ApplyLinearImpulse(b2Vec2(50, 50), Body->GetPosition(), true);
}

void Profesor::mover(int nuevax, int nuevay) {
	sprite.setPosition(nuevax, nuevay);
	setX(nuevax);
	setY(nuevay);
}

void Profesor::moverX(int nuevax) {
	sprite.move(nuevax, getY());
	setX(nuevax);
}

void Profesor::moverY(int nuevay) {
	sprite.move(getX(), nuevay);
	setY(nuevay);
}

void Profesor::escalar(float nuevoAlto, float nuevoAncho) {
	sprite.scale(nuevoAlto, nuevoAncho);
}

void Profesor::flip() {
	if (!flipped) {
		sprite.setScale({ -2, 2 });
		this->flipped = true;
	}
}

void Profesor::unflip() {
	if (flipped) {
		sprite.setScale({ 2, 2 });
		this->flipped = false;
	}
}

void Profesor::swapflip() {
	if (!flipped) {
		flip();
		setFlipped(true);
	}
	else {
		unflip();
		setFlipped(false);
	}
}

sf::Texture Profesor::getTextura() { return texture; }
bool Profesor::setTextura(std::string Nombre) { return texture.loadFromFile(Nombre); }

sf::Sprite Profesor::getSprite() { return animatedSprite; }
void Profesor::setSprite(sf::Texture Personaje) {
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, cAnchoProtagonista, cAltoProtagonista));
}

Profesor::~Profesor() {
	std::cout << "Destruyendo Personaje." << std::endl;
}

void Profesor::setX(const int& nuevax) { posx = nuevax; }
void Profesor::setY(const int& nuevay) { posy = nuevay; }
int& Profesor::getX() { return posx; }
int& Profesor::getY() { return posy; }

void Profesor::setAncho(const int & nuevoancho) { ancho = nuevoancho; }
int & Profesor::getAncho() { return ancho; }

void Profesor::setAlto(const int & nuevoalto) { alto = nuevoalto; }
int & Profesor::getAlto() { return alto; }

void Profesor::setFlipped(const bool & flipeado) { flipped = flipeado; }
bool & Profesor::getFlipped() { return flipped; }

b2Body* Profesor::getBody() { return Body; }
sf::RectangleShape Profesor::getShape() { return rectangulo; }
b2Vec2 Profesor::getLinearVelocity() { return Body->GetLinearVelocity(); }

void Profesor::startContact() { m_contacting++; }
void Profesor::endContact() { m_contacting--; }

int Profesor::getEntityType() { return PERSONAJE; }

void Profesor::setMoverArriba() { moverArriba = true; }
void Profesor::setMoverAbajo() { moverAbajo = true; }
void Profesor::setMoverDerecha() { moverDerecha = true; }
void Profesor::setMoverIzquierda() { moverIzquierda = true; }
void Profesor::setSaltando() { saltando = true; }
void Profesor::removeMoverArriba() { moverArriba = false; }
void Profesor::removeMoverAbajo() { moverAbajo = false; }
void Profesor::removeMoverDerecha() { moverDerecha = false; }
void Profesor::removeMoverIzquierda() { moverIzquierda = false; }
void Profesor::removeSaltando() { saltando = false; }
bool Profesor::isMoviendoArriba() { return moverArriba; }
bool Profesor::isMoviendoAbajo() { return moverAbajo; }
bool Profesor::isMoviendoDerecha() { return moverDerecha; }
bool Profesor::isMoviendoIzquierda() { return moverIzquierda; }
bool Profesor::isSaltando() { return saltando; }