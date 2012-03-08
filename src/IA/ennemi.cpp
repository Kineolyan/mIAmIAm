/*
 * ennemi.cpp
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#include "ennemi.h"

Ennemi::Ennemi(Case* position):
	m_position(position)
{}

Ennemi::Ennemi(Case& position):
	m_position(&position)
{}

Ennemi::~Ennemi()
{}

int Ennemi::effectif() const
{	return m_position->nbOccupants();	}

Case* Ennemi::position()
{	return m_position;	}
