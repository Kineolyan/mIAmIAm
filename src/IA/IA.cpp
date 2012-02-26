/*
 * IA.cpp
 *
 *  Created on: 27 janv. 2012
 *      Author: oliv
 */

#include "IA.h"
#include "joueurIA.h"
#include "../util/max.hpp"
#include "strategies/strategieSimple.h"

using namespace std;

const int NOMBRE_DE_DEPLACEMENTS_MAX = 3;

IA::IA(JoueurIA& joueur, Espece espece):
	m_joueur(joueur),
	m_plateau(NULL),
	m_espece(VAMPIRE==espece? VAMPIRE: LOUP),
	m_especeEnnemie(VAMPIRE==espece? LOUP: VAMPIRE),
	m_cible(NULL),
	m_groupes(),
	m_ennemis(),
	m_humains(),
	m_deplacements() {
	m_deplacements.reserve(NOMBRE_DE_DEPLACEMENTS_MAX);
}

IA::~IA() {
	m_groupes.clear();
	m_ennemis.clear();
	m_humains.clear();

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
	m_groupes.push_back(Groupe(*this, &(zone(x, y))));
	m_groupes.back().strategie(StrategieSimple::instance());

	return m_groupes.back();
}

void IA::supprimerGroupe(int x, int y) {
	Groupes::iterator groupe = m_groupes.begin(),
			_end = m_groupes.end();
	for ( ; groupe!=_end; ++groupe) {
		if (groupe->position().estEn(x, y)) {
			m_groupes.erase(groupe);
			break;
		}
	}
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
	deplacer(groupe.x(), groupe.y(), x, y, taille);

	Groupe& nouveauGroupe = ajouterGroupe(x, y);
	nouveauGroupe.cible(choisirCible(nouveauGroupe));
}

Case& IA::ajouterEnnemi(int x, int y) {
	m_ennemis.push_back(&(zone(x, y)));

	return *(m_ennemis.back());
}

void IA::supprimerEnnemi(int x, int y) {
	m_ennemis.remove(&(zone(x, y)));
}

Case& IA::ajouterHumains(int x, int y) {
	m_humains.push_back(&(zone(x, y)));

	return *(m_humains.back());
}

void IA::supprimerHumains(int x, int y) {
	Humains::iterator humain = m_humains.begin(),
			_end = m_humains.end();
	for ( ; humain!=_end; ++humain) {
		if ((*humain)->estEn(x, y)) {
			m_humains.erase(humain);
			break;
		}
	}
}

/**
 * On met à jour la case du plateau
 * En plus, si la case est nouvellement possédée par l'ennemi, on l'ajoute
 * à notre liste, et on enlève les humains ou un de nos groupes s'il y en
 * avait un avant.
 * Si la case devient vide, on supprime les occupants.
 *
 * @param x: abscisse de la case changeante
 * @param y: ordonnée de la case
 * @param h: nombre mis à jour d'humains
 * @param v: nombre de vampires
 * @param l: nombre de loups-garous
 *
 * @return: void
 */
void IA::update(int x, int y, int h, int v, int l) {
	Espece especePrecendente = zone(x, y).occupant(),
		especeAjoutee = zone(x, y).update(h, v, l);

	if (m_especeEnnemie==especeAjoutee) {
		ajouterEnnemi(x, y);

		if (m_espece==especePrecendente) {
			supprimerGroupe(x, y);
		}
		else if (HUMAIN==especePrecendente) {
			supprimerHumains(x, y);
		}
	}
	else if (VIDE==especeAjoutee) {
		/* Ce ne peut être qu'un groupe ou des ennemis
		Si c'était des humains, ils ont été remplacés par l'ennemi (cas précédent)
		ou par nous, et donc la cible n'est plus dans la liste */
		supprimerGroupe(x, y);
		supprimerEnnemi(x, y);
	}
}

void IA::initialiserCibles() {
	m_groupes.front().cible(choisirCible(m_groupes.front()));
}

/**
 * Définit une cible pour un groupe.
 * On choisit les humains en premier, puis les ennemis
 */
Case* IA::choisirCible(const Groupe& groupe) {
	Case* cible = NULL;

	// On cherche parmi les humains
	Humains::iterator maison = m_humains.begin(),
			endHumains = m_humains.end();
	int distanceMax = m_plateau->distanceMax()+1, distanceCible,
			xGroupe = groupe.x(), yGroupe = groupe.y();

	for ( ; maison!=endHumains; ++maison) {
		distanceCible = (*maison)->distance(xGroupe, yGroupe);
		if (distanceMax > distanceCible
		&& (*maison)->nbOccupants() <= groupe.taille()) {
			distanceMax = distanceCible;
			cible = *maison;
		}
	}

	if (NULL!=cible) {
		m_humains.remove(cible);
		return cible;
	}

	// Aucune cible trouvée parmi les humains
	Ennemis::iterator ennemi = m_ennemis.begin(),
			endEnnemis = m_ennemis.end();
	distanceMax = m_plateau->distanceMax()+1;
	for ( ; ennemi!=endEnnemis; ++ennemi) {
		distanceCible = (*ennemi)->distance(xGroupe, yGroupe);
		if (distanceMax > distanceCible
		&& 1.5*(*ennemi)->nbOccupants() <= groupe.taille()) {
			distanceMax = distanceCible;
			cible = *ennemi;
		}
	}

	if (NULL!=cible) {
		m_ennemis.remove(cible);
	}

	return cible;
}

void IA::placer(int x, int y) {
	m_x = x;
	m_y = y;
}

/**
 * Vérifie que tous les groupes ont bien la bonne cible (pas supprimée)
 * et que des ennemis ne sont pas trop proches
 */
void IA::verifierCibles() {

}

void IA::jouer() {
	// créer un groupe ou faire jouer les groupes
	// Création statique d'un groupe
	static bool premierTour = false;

	if (premierTour) {
		premierTour = false;
		separerGroupe(m_groupes.front(), 5, 3, 1);
		effectuerDeplacements();
	}
	else {
		// Surveiller l'état des cibles et si besoin réassigner
		verifierCibles();

		// Faire jouer les groupes
		Groupes::iterator groupe = m_groupes.begin(),
				end = m_groupes.end();
		ListeMax<double, Groupe> choix(NOMBRE_DE_DEPLACEMENTS_MAX);
		for ( ; groupe!=end; ++groupe) {
			choix.ajouter(groupe->preparerAction(), *groupe);
		}

		ListeMax<double, Groupe>::iterator 
			groupeChoisi = choix.begin(),
			endChoix = choix.end();
		for ( ; groupeChoisi!=endChoix; ++groupeChoisi) {
			groupeChoisi->jouerAction();
		}

		effectuerDeplacements();
	}
}

void IA::attaquer(int cibleX, int cibleY) {
	m_joueur.attaquer(cibleX, cibleY);
}

void IA::deplacer(int fromX, int fromY, int toX, int toY, int nombre) {
	m_deplacements.push_back(Deplacement(fromX, fromY, toX, toY, nombre));
}

void IA::effectuerDeplacements() {
	m_joueur.deplacer(m_deplacements);
	m_deplacements.clear();
}

/**
 * Vérifie que le jeu a bien évolué comme l'IA
 *
 * @throw: runtime_error
 */
void IA::verifierSituation(){
	Groupes::iterator groupe = m_groupes.begin(),
			_end = m_groupes.end();
	bool reattribuerCibles = false;
	for ( ; groupe!=_end; ++groupe) {
		if (groupe->position().occupant()!=m_espece) {
			cerr << "Un des groupes est mal placé en "
					<< groupe->x() << "-" <<  groupe->y();
			if (NULL==groupe->cible()) {
				groupe->supprimerCible();
				reattribuerCibles = true;
			}
		}
	}

	if (reattribuerCibles) {
		groupe = m_groupes.begin();
		for ( ; groupe!=_end; ++groupe) {
			if (NULL==groupe->cible()) {
				choisirCible(*groupe);
			}
		}
	}
}

