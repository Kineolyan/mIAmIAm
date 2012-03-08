/*
 * humain.cpp
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#include "humain.h"

Humain::Humain(Case* position):
	m_position(position)
{}

Humain::Humain(Case& position):
	m_position(&position)
{}

Humain::~Humain()
{}

int Humain::effectif() const
{	return m_position->nbOccupants();	}

Case* Humain::position()
{	return m_position;	}
