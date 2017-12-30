#pragma once
#include "Personaje.h"
#include <Box2D/Box2D.h>
#include "Personaje.h"

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

