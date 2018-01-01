#include "stdafx.h"
#include "MyContactListener.h"

MyContactListener::MyContactListener()
{
}


MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact* contact) {
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	//check if fixture A was a ball
	if (bodyUserData) {
		if (static_cast<b2Body*>(bodyUserData)->GetType() == b2_staticBody) {
			std::cout << "Suelo" << std::endl;
		} else {
			switch (static_cast<Personaje*>(bodyUserData)->getEntityType()) {
			case PERSONAJE:
				static_cast<Personaje*>(bodyUserData)->startContact();
				static_cast<Personaje*>(bodyUserData)->removeSaltando();
				break;
			default:
				break;
			}
		}
	}

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {
		if (static_cast<b2Body*>(bodyUserData)->GetType() == b2_staticBody)
			std::cout << "Suelo" << std::endl;
		else {
			switch (static_cast<Personaje*>(bodyUserData)->getEntityType()) {
			case PERSONAJE:
				static_cast<Personaje*>(bodyUserData)->startContact();
				break;
			default:
				break;
			}
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact) {
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	//check if fixture A was a ball
	if (bodyUserData) {
		if (static_cast<b2Body*>(bodyUserData)->GetType() == b2_staticBody) {

		} else {
			switch (static_cast<Personaje*>(bodyUserData)->getEntityType()) {
			case PERSONAJE:
				static_cast<Personaje*>(bodyUserData)->endContact();
				break;
			default:
				break;
			}
		}
	}

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {
		if (static_cast<b2Body*>(bodyUserData)->GetType() == b2_staticBody) {

		} else {
			switch (static_cast<Personaje*>(bodyUserData)->getEntityType()) {
			case PERSONAJE:
				static_cast<Personaje*>(bodyUserData)->endContact();
				break;
			default:
				break;
			}
		}
	}
}