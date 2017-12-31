#include "stdafx.h"
#include "Personaje.h"

Personaje::Personaje(std::string Nombre) :
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
	walkingAnimationRight.setSpriteSheet(this->texture);
	escalar(altoinicial, anchoinicial);
	animatedSprite.setOrigin({ animatedSprite.getLocalBounds().width / 2, 0 });
	removeMoverArriba();
	removeMoverAbajo();
	removeMoverDerecha();
	removeMoverIzquierda();
	removeSaltando();
	flipped = false;

	// prueba animacion
	walkingAnimationRight.addFrame(sf::IntRect(0, 0, cAnchoProtagonista, cAltoProtagonista));
	walkingAnimationRight.addFrame(sf::IntRect(cAnchoProtagonista, 0, cAnchoProtagonista, cAltoProtagonista));
	walkingAnimationRight.addFrame(sf::IntRect(cAnchoProtagonista * 2, 0, cAnchoProtagonista, cAltoProtagonista));
	walkingAnimationRight.addFrame(sf::IntRect(cAnchoProtagonista * 3, 0, cAnchoProtagonista, cAltoProtagonista));
	walkingAnimationRight.addFrame(sf::IntRect(cAnchoProtagonista * 4, 0, cAnchoProtagonista, cAltoProtagonista));
	walkingAnimationRight.addFrame(sf::IntRect(cAnchoProtagonista * 5, 0, cAnchoProtagonista, cAltoProtagonista));

	currentAnimation = &walkingAnimationRight;
	animatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition((float)posxinicial , (float)posyinicial);
	// fin prueba animacion
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

	this->frameTime = frameClock.restart();

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
		currentAnimation = &walkingAnimationRight;
		desiredVelocity = aceleracion;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange, 0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	}
	else if (isMoviendoIzquierda()) {
		flip();
		currentAnimation = &walkingAnimationRight;
		desiredVelocity = -aceleracion;
		float velocityChange = desiredVelocity - momentum.x;
		b2Vec2 impulse(Body->GetMass() * velocityChange, 0);
		Body->ApplyLinearImpulse(impulse, Body->GetWorldCenter(), true);
	}
	else {
		animatedSprite.stop();
		removeMoverDerecha();
		removeMoverIzquierda();
	}

	/*if (isSaltando()) {
		Body->ApplyForce(b2Vec2(0, 500), Body->GetWorldCenter(),true);
	}*/

	if (m_contacting > 0) {

	}
	animatedSprite.play(*currentAnimation);
	mover(SCALE * Body->GetPosition().x, SCALE * Body->GetPosition().y);
	// update AnimatedSprite
	animatedSprite.update(frameTime);
}

void Personaje::setFisicaSprite(b2World& localWorld) {
	animatedSprite.play(*currentAnimation);
	BodyDef.position = b2Vec2(this->posx, this->posy);
	BodyDef.type = b2_dynamicBody;
	Body = localWorld.CreateBody(&BodyDef);

	//Shape.SetAsBox(sprite.getGlobalBounds().width / 2, animatedSprite.getGlobalBounds().height / 2);
	Shape.SetAsBox(animatedSprite.getGlobalBounds().width / 2, animatedSprite.getGlobalBounds().height / 2);

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
	animatedSprite.setPosition(nuevax, nuevay);
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
	animatedSprite.scale(nuevoAlto, nuevoAncho);
}

void Personaje::flip() {
	if (!flipped) {
		animatedSprite.setScale({ -2, 2 });
		this->flipped = true;
	}
}

void Personaje::unflip() {
	if (flipped) {
		animatedSprite.setScale({ 2, 2 });
		this->flipped = false;
	}
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

sf::Texture Personaje::getTextura() { return texture; }
bool Personaje::setTextura(std::string Nombre) {
	if (!texture.loadFromFile(Nombre))
	{
		std::cout << "Failed to load player animatedSpritesheet!" << std::endl;
		return false;
	}
	return true;
}

sf::Sprite Personaje::getSprite() { return animatedSprite; }

void Personaje::setSprite(sf::Texture Personaje) {
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, cAnchoProtagonista * 6, cAltoProtagonista));
}

AnimatedSprite Personaje::getAnimatedSprite() { return animatedSprite; }

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

void Personaje::setFlipped(const bool & flipeado) { flipped = flipeado; }
bool & Personaje::getFlipped() { return flipped; }

b2Body* Personaje::getBody() { return Body; }
sf::RectangleShape Personaje::getShape() { return rectangulo; }
b2Vec2 Personaje::getLinearVelocity() { return Body->GetLinearVelocity(); }

void Personaje::startContact() { m_contacting++; }
void Personaje::endContact() { m_contacting--; }

int Personaje::getEntityType() { return PERSONAJE; }

void Personaje::setMoverArriba() { moverArriba = true; }
void Personaje::setMoverAbajo() { moverAbajo = true; }
void Personaje::setMoverDerecha() { moverDerecha = true; }
void Personaje::setMoverIzquierda() { moverIzquierda = true; }
void Personaje::setSaltando() { saltando = true; }
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