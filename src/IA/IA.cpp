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
	if (VAMPIRE==espece) {
		m_espece = VAMPIRE;
		m_especeEnnemie = LOUP;
	}
	else {
		m_espece = LOUP;
		m_especeEnnemie = VAMPIRE;
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
		cerr << e.what() << endl;
		throw runtime_error("Impossible de creer le plateau");
	}
}

Case& IA::zone(int x, int y)
{	return m_plateau->get(x, y);	}

Plateau& IA::plateau()
{	return *m_plateau;	}

void IA::reset() {
	if (NULL!=m_plateau) {
		delete m_plateau;
	}
}

Groupe& IA::ajouterGroupe(int x, int y) {
	m_groupes.push_back(Groupe(*this, *m_plateau, &(zone(x, y))));

	return m_groupes.back();
}

void IA::ajouterEnnemi(int x, int y) {
	//m_humains.push_back(&(zone(x, y)));
}

Case& IA::ajouterHumains(int x, int y) {
	m_humains.push_back(&(zone(x, y)));

	return *(m_humains.back());
}

/**
 * Sépare un groupe en deux, en déplaçant une partie des unités du groupe donné
 *
 * @param groupe: Groupe initial à séparer
 * @param x: abscisse du nouveau groupe
 * @param y: ordonnée du nouveau groupe
 * @param taille: taille du nouveau groupe
 */
void IA::separerGroupe(Groupe& groupe, int x, int y, int taille) {
	m_joueur.deplacer(groupe.x(), groupe.y(), x, y, taille);

	Groupe& nouveauGroupe = ajouterGroupe(x, y);
	nouveauGroupe.cible(choisirCible(nouveauGroupe));
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
	zone(x, y).update(h, v, l);
}

void IA::initialiserCibles() {
	m_groupes.front().cible(choisirCible(m_groupes.front()));
}

Case* IA::choisirCible(const Groupe& groupe) {
	Case* cible = NULL;
	list<Case*>::iterator maison = m_humains.begin(),
			_end = m_humains.end();
	int distanceMax = m_plateau->distanceMax(), distanceCible;

	for ( ; maison!=_end; ++maison) {
		distanceCible = (*maison)->distance(groupe.x(), groupe.y());
		if (distanceMax > distanceCible) {
			distanceMax = distanceCible;
			cible = *maison;
		}
	}

	if (NULL!=cible) {
		m_humains.remove(cible);
	}

	return cible;
}

void IA::placer(int x, int y) {
	m_x = x;
	m_y = y;
}

void IA::jouer() {
	// créer un groupe ou faire jouer les groupes
	// Création statique d'un groupe
	static bool premierTour = true;

	if (premierTour) {
		premierTour = false;
		separerGroupe(m_groupes.front(), 5, 3, 1);
	}
	else {
		list<Groupe>::iterator groupe = m_groupes.begin(),
				end = m_groupes.end(),
				groupeChoisi;
		double scoreMax = -1, score;

		for ( ; groupe!=end; ++groupe) {
			score = groupe->preparerAction();
			if (score > scoreMax) {
				scoreMax = score;
				groupeChoisi = groupe;
			}
		}

		groupeChoisi->jouerAction();
	}
}

//void IA::choisirCaseSuivante() {
//	int max = m_plateau->distanceMax(),
//		distance, nextX, nextY;
//	for (int i =-1; i<2; ++i) {
//		for (int j=-1; j<2; ++j) {
//			if (!(0==i && 0==j) && m_plateau->dansPlateau(m_x+i, m_y+j)) {
//				Plateau::Case& place = zone(m_x+i, m_y+j);
//				distance = place.distance(m_cible);
//				if (place.estOccupeePar(Plateau::Case::VIDE) && distance < max) {
//					max = distance;
//					nextX = m_x + i;
//					nextY = m_y + j;
//				}
//			}
//		}
//	}
//
//	// Aller à cette case
//	m_joueur.deplacer(m_x, m_y, nextX, nextY, zone(m_x, m_y).nbOccupants());
//	m_x = nextX;
//	m_y = nextY;
//}

void IA::attaquer(int cibleX, int cibleY) {
	m_joueur.attaquer(cibleX, cibleY);
}

void IA::deplacer(int fromX, int fromY, int toX, int toY, int nombre) {
	m_joueur.deplacer(fromX, fromY, toX, toY, nombre);
}

