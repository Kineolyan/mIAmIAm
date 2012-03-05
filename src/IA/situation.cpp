/*
 * situation.cpp
 *
 *  Created on: 2 mars 2012
 *      Author: oliv
 */

#include "situation.h"

Situation::Situation(Plateau& plateau):
	m_plateau(plateau),
	m_evolutions()
{}

Situation::Situation(const Situation& org):
	m_plateau(org.m_plateau),
	m_evolutions(org.m_evolutions)
{}

Situation::~Situation()
{}

void Situation::ajouterDeplacement(Espece espece,
		int xFrom, int yFrom, int xTo, int yTo, int nombre) {
	Evolutions::iterator position = m_evolutions.begin(),
			_end = m_evolutions.end();

	// Evoluer la case précédente
	bool positionTrouvee = false;
	for ( ; position!=_end; ++position) {
		if (position->estEn(xFrom, yFrom)) {
			positionTrouvee = true;
			position->evoluer(espece, -nombre);
		}
	}
	if (!positionTrouvee) {
		Case c = m_plateau.get(xFrom, yFrom);
		c.evoluer(espece, -nombre);
		m_evolutions.push_back(c);
	}

	// Evoluer la case destination
	positionTrouvee = false;
	position = m_evolutions.begin();
	for ( ; position!=_end; ++position) {
		if (position->estEn(xTo, yTo)) {
			positionTrouvee = true;
			position->evoluer(espece, nombre);
		}
	}
	if (!positionTrouvee) {
		Case c = m_plateau.get(xTo, yTo);
		c.evoluer(espece, nombre);
		m_evolutions.push_back(c);
	}
}

const Situation::Evolutions& Situation::evolutions() const
{	return m_evolutions;	}

Case* Situation::get(int x, int y) {
	Evolutions::iterator position = m_evolutions.begin(),
		_end = m_evolutions.end();

	// Evoluer la case précédente
	for ( ; position!=_end; ++position) {
		if (position->estEn(x, y)) {
			return &*position;
		}
	}

	return &m_plateau.get(x, y);
}

bool Situation::dansPlateau(int x, int y) const {
	return m_plateau.dansPlateau(x, y);
}
