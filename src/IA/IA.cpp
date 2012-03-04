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

IA::IA(JoueurIA& joueur):
	m_joueur(joueur),
	m_plateau(NULL),
	m_espece(VAMPIRE),
	m_especeEnnemie(LOUP),
	m_cible(NULL),
	m_groupes(),
	m_ennemis(),
	m_humains(),
	m_cibles(),
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

void IA::espece(Espece espece) {
	m_espece = espece;
	m_especeEnnemie = VAMPIRE==espece? LOUP: VAMPIRE;
}

const Espece IA::espece() const
{	return m_espece;	}

const Espece IA::especeEnnemie() const
{	return m_especeEnnemie;	}

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
	m_groupes.push_back(Groupe(*this, &zone(x, y)));
	m_groupes.back().strategie(StrategieSimple::instance());

	return m_groupes.back();
}

Groupe& IA::ajouterGroupe(int x, int y, int taille) {
	m_groupes.push_back(Groupe(*this, &zone(x, y), taille));
	m_groupes.back().strategie(StrategieSimple::instance());

	return m_groupes.back();
}

void IA::supprimerGroupe(int x, int y) {
	Groupes::iterator groupe = m_groupes.begin(),
			_end = m_groupes.end();
	for ( ; groupe!=_end; ++groupe) {
		if (groupe->position()->estEn(x, y)) {
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

	Groupe& nouveauGroupe = ajouterGroupe(x, y, taille);
	nouveauGroupe.cible(choisirCible(nouveauGroupe));
}

Ennemi& IA::ajouterEnnemi(int x, int y) {
	m_ennemis.push_back(Ennemi(zone(x, y)));

	return m_ennemis.back();
}

void IA::supprimerEnnemi(int x, int y) {
	Ennemis::iterator ennemi = m_ennemis.begin(),
			_end = m_ennemis.end();
	for ( ; ennemi!=_end; ++ennemi) {
		if (ennemi->position()->estEn(x, y)) {
			m_ennemis.erase(ennemi);
			break;
		}
	}
}

Humain& IA::ajouterHumains(int x, int y) {
	m_humains.push_back(Humain(zone(x, y)));

	return m_humains.back();
}

void IA::supprimerHumains(int x, int y) {
	Humains::iterator humain = m_humains.begin(),
			_end = m_humains.end();
	for ( ; humain!=_end; ++humain) {
		if (humain->position()->estEn(x, y)) {
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
		if (LOUP!=especePrecendente) {
			ajouterEnnemi(x, y);
		}

		if (m_espece==especePrecendente) {
			supprimerGroupe(x, y);
		}
		else if (HUMAIN==especePrecendente) {
			supprimerHumains(x, y);
		}
	}
	else if (VIDE==especeAjoutee) {
		/* Ce ne peut être qu'un groupe d'amis ou des ennemis
		Si c'était des humains, ils ont été remplacés par l'ennemi (cas précédent)
		ou par nous, et donc la cible n'est plus dans la liste */
		if (m_espece==especePrecendente) {
			supprimerGroupe(x, y);
		}
		else if (m_especeEnnemie==especePrecendente) {
			supprimerEnnemi(x, y);
		}
	}
	// On vérifie nos groupes après
}

void IA::initialiserCibles() {
	m_groupes.front().cible(choisirCible(m_groupes.front()));
}

/**
 * Définit une cible pour un groupe.
 * On choisit les humains en premier, puis les ennemis
 */
Cible* IA::choisirCible(Groupe& groupe) {
	int distanceMax = m_plateau->distanceMax()+1, distanceCible,
			xGroupe = groupe.x(), yGroupe = groupe.y();

	// On cherche parmi les humains
	{
		Humains::iterator maison = m_humains.begin(),
				end = m_humains.end(),
				cible = end;
		for ( ; maison!=end; ++maison) {
			if (!maison->estCible()) {
				distanceCible = maison->position()->distance(xGroupe, yGroupe);
				if (distanceMax > distanceCible
				&& maison->effectif() <= groupe.effectif()) {
					distanceMax = distanceCible;
					cible = maison;
				}
			}
		}

		if (end!=cible) {
			m_cibles.push_back(new CibleHumaine(groupe, *cible));
			return m_cibles.back();
		}
	}

	{
		// Aucune cible trouvée parmi les humains
		Ennemis::iterator ennemi = m_ennemis.begin(),
				end = m_ennemis.end(),
				cible = end;
		distanceMax = m_plateau->distanceMax()+1;
		for ( ; ennemi!=end; ++ennemi) {
			if (!ennemi->estCible()) {
				distanceCible = ennemi->position()->distance(xGroupe, yGroupe);
				if (distanceMax > distanceCible
				&& 1.5*ennemi->effectif() <= groupe.effectif()) {
					distanceMax = distanceCible;
					cible = ennemi;
				}
			}
		}

		if (end!=cible) {
			// TODO: Utiliser des smart pointers (prévu pour ça)
			m_cibles.push_back(new CibleEnnemie(groupe, *cible));
			return m_cibles.back();
		}
	}

	// Auncune cible trouvée
	return NULL;
}

void IA::supprimerCible(Cible* cible) {
	Case* caseCible = cible->position();
	int xCible = caseCible->x(), yCible = caseCible->y();

	// On enlève la cible des ennemis/humains
	if (HUMAIN==caseCible->occupant()) {
		supprimerHumains(xCible, yCible);
	}
//	else if (m_especeEnnemie==caseCible->occupant()) {
//		supprimerEnnemi(xCible, yCible);
//	}

	// On détruit la cible
	m_cibles.remove(cible);

	delete cible;
}

void IA::annulerCible(Cible* cible) {
	// Supprimer la poursuite
	cible->annulerCible();

	// On détruit la cible
	m_cibles.remove(cible);

	delete cible;
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
	Groupes::iterator groupe = m_groupes.begin(),
			end = m_groupes.end();
	for ( ; groupe!=end; ++groupe) {
		if (NULL==groupe->cible()) {
			groupe->cible(choisirCible(*groupe));
		}
	}
}

void IA::jouer() {
	// créer un groupe ou faire jouer les groupes
	// Création statique d'un groupe
	static bool premierTour = true;

	if (premierTour) {
		premierTour = false;
		if (VAMPIRE==m_espece) {
			separerGroupe(m_groupes.front(), 27, 14, 3);
			separerGroupe(m_groupes.front(), 28, 13, 3);
			effectuerDeplacements();
		}
		else {
			separerGroupe(m_groupes.front(), 1, 0, 3);
			separerGroupe(m_groupes.front(), 0, 1, 3);
			effectuerDeplacements();
		}
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
//	Groupes::iterator groupe = m_groupes.begin(),
//			_end = m_groupes.end();
//	bool reattribuerCibles = false;
//	for ( ; groupe!=_end; ++groupe) {
//		if (groupe->position().occupant()!=m_espece) {
//			cerr << "Un des groupes est mal placé en "
//					<< groupe->x() << "-" <<  groupe->y();
//			if (NULL==groupe->cible()) {
//				groupe->supprimerCible();
//				reattribuerCibles = true;
//			}
//		}
//	}
//
//	if (reattribuerCibles) {
//		groupe = m_groupes.begin();
//		for ( ; groupe!=_end; ++groupe) {
//			if (NULL==groupe->cible()) {
//				choisirCible(*groupe);
//			}
//		}
//	}
}

//void IA::revoirStrategie() {
//
//}

