/*
 * plateau.cpp
 *
 *  Created on: 24 janv. 2012
 *      Author: oliv
 */

#include <cmath>
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

Case& Plateau::get(int l, int h) {
	if (0<=h && h<m_hauteur && 0<=l && l<m_largeur) {
		return m_plateau[h][l];
	}
	else {
		throw runtime_error("Acces hors limite");
	}
}

bool Plateau::dansPlateau(int l, int h)
{	return (0<=h && h<m_hauteur && 0<=l && l<m_largeur);	}

void Plateau::redimensionner(int hauteur, int largeur) {
	if (hauteur > (int)m_plateau.size()) {
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

const int Plateau::distanceMax() const
{	return m_largeur> m_hauteur? m_largeur: m_hauteur;	}

/* -- -- */

Case::Case():
	m_positionX(-1), m_positionY(-1),
	m_occupant(VIDE), m_nombre(0)
{}

Case::Case(int positionX, int positionY, const Espece occupant,
		const int nombre):
		m_positionX(positionX), m_positionY(positionY),
		m_occupant(occupant), m_nombre(nombre)
{}

Case::Case(int positionX, int positionY,
		int nbHumains, int nbVampires, int nbLoups):
		m_positionX(positionX), m_positionY(positionY),
		m_occupant(VIDE), m_nombre(0) {
	update(nbHumains, nbVampires, nbLoups);
}

Case::Case(const Case& original):
		m_positionX(original.m_positionX),
		m_positionY(original.m_positionY),
		m_occupant(original.m_occupant),
		m_nombre(original.m_nombre)
{}

int Case::x() const
{	return m_positionX;	}

int Case::y() const
{	return m_positionY;	}

void Case::update(const Espece occupant, const int nombre) {
	if (nombre>0) {
		m_occupant = occupant;
		m_nombre = nombre;
	}
	else {
		m_nombre = 0;
		m_occupant = VIDE;
	}
}

/**
 * Met à jour la case du plateau et renvoie l'espèce mise à jour
 * @param nbHumains est le nombre d'humains dans la case
 * @param nbVampires est le nombre de vampires dans la case
 * @param nbLoups est le nombre de loups dans la case
 *
 * @return l'espèce mise à jour dans la case
 */
Espece Case::update(int nbHumains, int nbVampires, int nbLoups) {
	if (0!=nbHumains) {
		update(HUMAIN, nbHumains);
		return HUMAIN;
	}
	else if (0!=nbVampires) {
		update(VAMPIRE, nbVampires);
		return VAMPIRE;
	}
	else if (0!=nbLoups) {
		update(LOUP, nbLoups);
		return LOUP;
	}
	else {
		reset();
		return VIDE;
	}
}

void Case::evoluer(const Espece occupant, const int nombre) {
	if (VIDE!=occupant) {
		m_nombre+= nombre;
		if (m_nombre==0) {
			m_occupant = VIDE;
		}
		else if (m_nombre<0) {
			throw runtime_error("Impossible de deplacer plus d'unites qu'il n'y en a.");
		}
	}
	else {
		reset();
	}
}

void Case::placer(int x, int y) {
	m_positionX = x;
	m_positionY = y;
}

/**
 * Détermine si la case est bien à la position indiquée
 * @param x donne la colonne
 * @param y donne la ligne
 *
 * @return true si la case est bien où on le demande
 */
bool Case::estEn(int x, int y) const
{	return x==m_positionX && y==m_positionY;	}

bool Case::estOccupee() const {
	return VIDE==m_occupant;
}

bool Case::estOccupeePar(const Espece espece) const {
	return espece==m_occupant;
}

int Case::nbOccupants() const
{	return m_nombre;	}

Espece Case::occupant() const
{	return m_occupant;	}

void Case::reset() {
	m_occupant = VIDE;
	m_nombre = 0;
}

const int Case::distance(int positionX, int positionY) const {
	int distanceX = vabs(positionX - m_positionX),
		distanceY = vabs(positionY - m_positionY);

	return tMaximum(distanceX, distanceY);
}

const int Case::distance(const Case& zone) const {
	return distance(zone.m_positionX, zone.m_positionY);
}

const int Case::distance(const Case* zone) const {
	return distance(zone->m_positionX, zone->m_positionY);
}
