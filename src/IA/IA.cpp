/*
 * IA.cpp
 *
 *  Created on: 27 janv. 2012
 *      Author: oliv
 */

#include "IA.h"

using namespace std;

IA::IA(Espece espece):
	m_plateau(NULL),
	m_espece(),
	m_especeEnnemie(),
	m_cible(NULL),
	m_groupes(),
	m_ennemis(),
	m_humains() {
	if (Plateau::Case::VAMPIRE==espece) {
		m_espece = Plateau::Case::VAMPIRE;
		m_especeEnnemie = Plateau::Case::LOUP;
	}
	else {
		m_espece = Plateau::Case::LOUP;
		m_especeEnnemie = Plateau::Case::VAMPIRE;
	}
}

IA::~IA() {
	if (NULL!=m_plateau) {
		delete m_plateau;
	}
}

void IA::creerPlateau(int hauteur, int largeur) {
	try {
		m_plateau = new Plateau(hauteur, largeur);
		cout << "La grille contient " << hauteur << " lignes et "
				<< largeur << " colonnes." << endl;
	}
	catch(const exception& e) {
		throw runtime_error("Impossible de creer le plateau");
	}
}

inline Plateau::Case& IA::zone(int x, int y)
{	return m_plateau->get(x, y);	}

void IA::reset() {
	if (NULL!=m_plateau) {
		delete m_plateau;
	}
}


void IA::ajouterAmis(int x, int y, int nombre) {
	zone(x, y).update(m_espece, nombre);
	m_groupes.push_back(&(zone(x, y)));
}

void IA::ajouterEnnemis(int x, int y, int nombre) {
	zone(x, y).update(m_especeEnnemie, nombre);
	m_humains.push_back(&(zone(x, y)));
}

void IA::ajouterHumains(int x, int y, int nombre) {
	zone(x, y).update(Plateau::Case::HUMAIN, nombre);
	m_humains.push_back(&(zone(x, y)));
}

void IA::supprimerHumains(int x, int y) {
	list<Plateau::Case*>::iterator groupe = m_humains.begin(),
			_end = m_humains.end();
	for ( ; groupe!=_end; ++groupe) {
		if ((*groupe)->estEn(x, y)) {
			m_humains.erase(groupe);
			return;
		}
	}
}

void IA::update(int x, int y, int h, int v, int l) {
	const bool caseHumaine = zone(x, y).estOccupeePar(Plateau::Case::HUMAIN);
	const Espece espece = zone(x, y).update(h, v, l);

	if (caseHumaine && Plateau::Case::VIDE==espece) {
		supprimerHumains(x, y);
	}
}

void IA::initialiserCibles() {
	list<Plateau::Case*>::iterator groupe = m_humains.begin(),
			_end = m_humains.end();
	int distance = m_plateau->distanceMax(), distanceCible;

	for ( ; groupe!=_end; ++groupe) {
		distanceCible = (*groupe)->distance(m_x, m_y);
		if (distance > distanceCible) {
			distance = distanceCible;
			m_cible = *groupe;
		}
	}
}

void IA::placer(int x, int y) {
	m_x = x;
	m_y = y;
}

void IA::jouer() {
	const int destinationX = m_cible->x(),
		destinationY = m_cible->y();

	if (m_cible->distance(m_x, m_y)==1) {
		// Attaquer la cible
	}

	int dx = 0, dy = 0;

	if (destinationX > m_x) {
		++dx;
	}
	else if (destinationX < m_x) {
		--dx;
	}

	if (destinationY > m_y) {
		++dy;
	}
	else if (destinationY < m_y) {
		--dy;
	}

	int distanceX = vabs(destinationX-m_x),
		distanceY = vabs(destinationY-m_y);
	while (!zone(m_x, m_y).estOccupeePar(Plateau::Case::VIDE)) {
		bool dpdx = distanceX >= distanceY,
			dpdy = distanceY >= distanceX;
		if (dpdx) {
			switch(dy) {
			case 1:
				dy = 0;
			case 0:
				dy = -1;
			case -1:
				dy = 1;
			}
		}
		else {
			switch(dx) {
			case 1:
				dx = 0;
			case 0:
				dx = -1;
			case -1:
				dx = 1;
			}
		}
	}
}


