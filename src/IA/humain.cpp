/*
 * humain.cpp
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#include "humain.h"
#include "cible.h"

Humain::Humain(Case* position):
	m_viseur(NULL),
	m_position(position)
{}

Humain::Humain(Case& position):
	m_viseur(NULL),
	m_position(&position)
{}

Humain::~Humain() {
	if (NULL!=m_viseur) {
		m_viseur->destructionCible();
	}
}

int Humain::effectif() const
{	return m_position->nbOccupants();	}

Case* Humain::position()
{	return m_position;	}

void Humain::poursuiviePar(Cible* cible) {
	m_viseur = cible;
}

void Humain::annulerPoursuite(){
	m_viseur = NULL;
}

bool Humain::estCible() const
{	return NULL!=m_viseur;	}
