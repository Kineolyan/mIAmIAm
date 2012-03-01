/*
 * ennemi.cpp
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#include "ennemi.h"
#include "cible.h"

Ennemi::Ennemi(Case* position):
	m_viseur(NULL),
	m_position(position)
{}

Ennemi::Ennemi(Case& position):
	m_viseur(NULL),
	m_position(&position)
{}

Ennemi::~Ennemi() {
	if (NULL!=m_viseur) {
		m_viseur->destructionCible();
	}
}

int Ennemi::effectif() const
{	return m_position->nbOccupants();	}

Case* Ennemi::position()
{	return m_position;	}

void Ennemi::poursuiviePar(Cible* cible) {
	m_viseur = cible;
}

void Ennemi::annulerPoursuite(){
	m_viseur = NULL;
}

bool Ennemi::estCible() const
{	return NULL!=m_viseur;	}
