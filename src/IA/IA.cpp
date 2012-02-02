/*
 * IA.cpp
 *
 *  Created on: 27 janv. 2012
 *      Author: oliv
 */

#include "IA.h"
#include "joueurIA.h"

using namespace std;

IA::IA(JoueurIA& joueur, Espece espece):
	m_joueur(joueur),
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

void IA::ajouterGroupe(int x, int y) {
	m_groupes.push_back(Groupe(m_joueur, *m_plateau, &zone(x, y)));
}

void IA::ajouterEnnemi(int x, int y, int nombre) {
	m_humains.push_back(&(zone(x, y)));
}

void IA::ajouterHumains(int x, int y) {
	m_humains.push_back(&(zone(x, y)));
}

//void IA::supprimerHumains(int x, int y) {
//	list<Plateau::Case*>::iterator groupe = m_humains.begin(),
//			_end = m_humains.end();
//	for ( ; groupe!=_end; ++groupe) {
//		if ((*groupe)->estEn(x, y)) {
//			m_humains.erase(groupe);
//			return;
//		}
//	}
//}

void IA::update(int x, int y, int h, int v, int l) {
	const bool caseHumaine = zone(x, y).estOccupeePar(Plateau::Case::HUMAIN);
	const Espece espece = zone(x, y).update(h, v, l);

	if (caseHumaine && Plateau::Case::VIDE==espece) {
		supprimerHumains(x, y);
	}
}

void IA::initialiserCibles() {
	m_groupes.front().cible(choisirCible());
}

Case* IA::choisirCible() {
	Case* cible = NULL;
	list<Plateau::Case*>::iterator groupe = m_humains.begin(),
			_end = m_humains.end();
	int distance = m_plateau->distanceMax(), distanceCible;

	for ( ; groupe!=_end; ++groupe) {
		distanceCible = (*groupe)->distance(m_x, m_y);
		if (distance > distanceCible) {
			distance = distanceCible;
			cible = *groupe;
		}
	}

	m_humains.remove(cible);
	return cible;
}

void IA::placer(int x, int y) {
	m_x = x;
	m_y = y;
}

void IA::jouer() {
	// créer un groupe ou faire jouer les groupes

	list<Groupe>::iterator groupe = m_groupes.begin(),
			end = m_groupes.end(),
			groupeChoisi;
	int scoreMax = -1, score;

	for ( ; groupe!=end; ++groupe) {
		score = groupe->preparerAction();
		if (score > scoreMax) {
			scoreMax = score;
			groupeChoisi = groupe;
		}
	}

	groupeChoisi->jouerAction();
}

void IA::choisirCaseSuivante() {
	int max = m_plateau->distanceMax(),
		distance, nextX, nextY;
	for (int i =-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			if (!(0==i && 0==j) && m_plateau->dansPlateau(m_x+i, m_y+j)) {
				Plateau::Case& place = zone(m_x+i, m_y+j);
				distance = place.distance(m_cible);
				if (place.estOccupeePar(Plateau::Case::VIDE) && distance < max) {
					max = distance;
					nextX = m_x + i;
					nextY = m_y + j;
				}
			}
		}
	}

	// Aller à cette case
	m_joueur.deplacer(m_x, m_y, nextX, nextY, zone(m_x, m_y).nbOccupants());
	m_x = nextX;
	m_y = nextY;
}

