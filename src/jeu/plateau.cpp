/*
 * plateau.cpp
 *
 *  Created on: 24 janv. 2012
 *      Author: oliv
 */

#include "plateau.h"

using namespace std;

Plateau::Plateau():
	m_hauteur(0),
	m_largeur(0),
	m_plateau(0)
{}

Plateau::Plateau(int hauteur, int largeur):
	m_hauteur(hauteur),
	m_largeur(largeur),
	m_plateau(hauteur) {
	for (int y=0; y<m_hauteur; ++y) {
		m_plateau[y] = vector<Case>(m_largeur);

		for (int x=0; x<m_largeur; ++x) {
			m_plateau[y][x].placer(x, y);
		}
	}
}

Plateau::Case& Plateau::get(int h, int l) {
	if (0<=h && h<m_hauteur && 0<=l && l<m_largeur) {
		return m_plateau[h][l];
	}
	else {
		throw runtime_error("Acces hors limite");
	}
}

void Plateau::redimensionner(int hauteur, int largeur) {
	if (hauteur > m_plateau.size()) {
		m_plateau.resize(hauteur);
		for (int i=m_hauteur; i<hauteur; ++i) {
			m_plateau[i].resize(largeur);
		}
	}
	m_hauteur = hauteur;

	if (largeur > m_largeur) {
		for (int i=0; i<m_hauteur; ++i) {
			m_plateau[i].resize(largeur);
		}
	}
	m_largeur = largeur;
}

/* -- -- */

Plateau::Case::Case():
	m_positionX(-1), m_positionY(-1),
	m_occupant(VIDE), m_nombre(0)
{}

Plateau::Case::Case(int positionX, int positionY, const Espece occupant,
		const int nombre):
		m_positionX(positionX), m_positionY(positionY),
		m_occupant(occupant), m_nombre(nombre)
{}

void Plateau::Case::update(const Espece occupant, const int nombre) {
	m_occupant = occupant;
	m_nombre = nombre;
}

void Plateau::Case::update(int nbHumains, int nbVampires, int nbLoups) {
	if (0!=nbHumains) {
		update(HUMAIN, nbHumains);
	}
	else if (0!=nbVampires) {
		update(LOUP, nbVampires);
	}
	else if (0!=nbLoups) {
		update(LOUP, nbLoups);
	}
}

void Plateau::Case::placer(int x, int y) {
	m_positionX = x;
	m_positionY = y;
}

bool Plateau::Case::estOccupeePar(const Espece espece) const {
	return espece==m_occupant;
}

int Plateau::Case::nbOccupants() const
{	return m_nombre;	}

void Plateau::Case::reset() {
	m_occupant = VIDE;
	m_nombre = 0;
}
