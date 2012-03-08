/*
 * IA.cpp
 *
 *  Created on: 27 janv. 2012
 *      Author: oliv
 */

#include "IA.h"
#include "joueurIA.h"
#include "../util/max.hpp"
#include "../util/sortedList.hpp"
#include "strategies/strategieSimple.h"
#include "strategies/strategieEvoluee.h"
#include "../util/timer.h"

using namespace std;

const int NOMBRE_DE_DEPLACEMENTS_MAX = 3;

IA::IA(JoueurIA& joueur):
	m_joueur(joueur),
	m_plateau(NULL),
	m_espece(VAMPIRE),
	m_especeEnnemie(LOUP),
	m_groupes(),
	m_ennemis(),
	m_humains(),
	m_deplacements() {
	m_deplacements.reserve(NOMBRE_DE_DEPLACEMENTS_MAX);
}

IA::~IA() {
	m_humains.clear();
	m_ennemis.clear();
	m_groupes.clear();

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
	m_humains.clear();
	m_ennemis.clear();
	m_groupes.clear();

	if (NULL!=m_plateau) {
		delete m_plateau;
	}
}

Groupe& IA::ajouterGroupe(int x, int y) {
	m_groupes.push_back(Groupe(*this, &zone(x, y)));
	m_groupes.back().strategie(StrategieEvoluee::instance());
	cout << "nouveau groupe en " << x << "-" << y << endl;

	return m_groupes.back();
}

Groupe& IA::ajouterGroupe(int x, int y, int taille) {
	m_groupes.push_back(Groupe(*this, &zone(x, y), taille));
	m_groupes.back().strategie(StrategieEvoluee::instance());
	cout << "nouveau groupe en " << x << "-" << y << endl;

	return m_groupes.back();
}

void IA::supprimerGroupe(int x, int y) {
	Groupes::iterator groupe = m_groupes.begin(),
			_end = m_groupes.end();
	list<Groupes::iterator> groupesASupprimer;
	for ( ; groupe!=_end; ++groupe) {
		if (groupe->position()->estEn(x, y)) {
			groupesASupprimer.push_back(groupe);
			cout << "groupe supprime en " << x << "-" << y << endl;
		}
	}

	while (!groupesASupprimer.empty()) {
		m_groupes.erase(groupesASupprimer.front());
		groupesASupprimer.pop_front();
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
	groupe.scinder(x, y, taille);
}

Ennemi& IA::ajouterEnnemi(int x, int y) {
	m_ennemis.push_back(Ennemi(zone(x, y)));
	cout << "nouvel ennemi en " << x << "-" << y << endl;

	return m_ennemis.back();
}

void IA::supprimerEnnemi(int x, int y) {
	Ennemis::iterator ennemi = m_ennemis.begin(),
			_end = m_ennemis.end();
	for ( ; ennemi!=_end; ++ennemi) {
		if (ennemi->position()->estEn(x, y)) {
			m_ennemis.erase(ennemi);
			cout << "ennemi supprime en " << x << "-" << y << endl;
			break;
		}
	}
}

Humain& IA::ajouterHumains(int x, int y) {
	m_humains.push_back(Humain(zone(x, y)));

	return m_humains.back();
}

int IA::nbHumainsRestants(){
	
	int nbTotal = 0;
	Humains::iterator hum;

	for (hum = m_humains.begin();hum!=m_humains.end();++hum){
		nbTotal += hum->effectif();
	}

	return nbTotal;
}
int IA::nbMaisonsRestantes()
{ return m_humains.size(); }

int IA::nbEnnemis(){

	int nbTotal = 0;
	Ennemis::iterator hum;

	for (hum = m_ennemis.begin();hum!=m_ennemis.end();++hum){
		nbTotal += hum->effectif();
	}
	return nbTotal;
}

void IA::supprimerHumains(int x, int y) {
	Humains::iterator humain = m_humains.begin(),
			_end = m_humains.end();
	for ( ; humain!=_end; ++humain) {
		if (humain->position()->estEn(x, y)) {
			m_humains.erase(humain);
			cout << "humain supprime en " << x << "-" << y << endl;
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
	Espece especePrecedente = zone(x, y).occupant(),
		especeAjoutee = zone(x, y).update(h, v, l);

	if (m_especeEnnemie==especeAjoutee) {
		ajouterEnnemi(x, y);

		if (m_espece==especePrecedente) {
			supprimerGroupe(x, y);
		}
		else if (HUMAIN==especePrecedente) {
			supprimerHumains(x, y);
		}
	}
	else if (VIDE==especeAjoutee) {
		/* Ce ne peut être qu'un groupe d'amis ou des ennemis
		Si c'était des humains, ils ont été remplacés par l'ennemi (cas précédent)
		ou par nous */
		/*if (m_espece==especePrecedente) {
			supprimerGroupe(x, y);
		}
		else */
		if (m_especeEnnemie==especePrecedente) {
			supprimerEnnemi(x, y);
		}
	}
	// On vérifie nos groupes après
}

void IA::jouer() {
	// créer un groupe ou faire jouer les groupes
	// Création statique d'un groupe
	static bool premierTour = true;

	if (premierTour) {
		premierTour = false;
		Groupe& groupeInitial = m_groupes.front();
		int xDebut = groupeInitial.x();
		int yDebut = groupeInitial.y();
		int tailleInitiale = groupeInitial.effectif() / 2;

		if (m_plateau->dansPlateau(xDebut, yDebut-1)) {
			separerGroupe(m_groupes.front(), xDebut, yDebut-1, 1);
		}
		else {
			separerGroupe(m_groupes.front(), xDebut, yDebut+1, 1);
		}

		if (m_plateau->dansPlateau(xDebut+1, yDebut)) {
			separerGroupe(m_groupes.front(), xDebut+1, yDebut, tailleInitiale);
		}
		else {
			separerGroupe(m_groupes.front(), xDebut-1, yDebut, tailleInitiale);
		}

		groupeInitial.preparerAction();
		groupeInitial.jouerAction();
		
		effectuerDeplacements();
		/*else {
			separerGroupe(m_groupes.front(), 1, 0, 3);
			separerGroupe(m_groupes.front(), 0, 1, 3);
			m_groupes.front().deplacer(1, 1);
			effectuerDeplacements();
		}*/
	}
	else {
		// Faire jouer les groupes
		Groupes::iterator groupe = m_groupes.begin(),
				end = m_groupes.end();
		/* On se concerte
		ListeMax<double, Groupe> choix(NOMBRE_DE_DEPLACEMENTS_MAX);
		for ( ; groupe!=end; ++groupe) {
			Get<Timer>().checkpoint();
			choix.ajouter(groupe->preparerAction(), *groupe);
			if (!Get<Timer>().checkTime()) {
				break;
			}
		}

		ListeMax<double, Groupe>::iterator 
			groupeChoisi = choix.begin(),
			endChoix = choix.end();
		for ( ; groupeChoisi!=endChoix; ++groupeChoisi) {
			groupeChoisi->jouerAction();
		}
		//*/

		//* On ordonne tous les déplacements par ordre d'importance
		SortedList<double, Groupe> choix;
		for ( ; groupe!=end; ++groupe) {
			Get<Timer>().checkpoint();
			choix.ajouter(groupe->preparerAction(), *groupe);
			if (!Get<Timer>().checkTime()) {
				break;
			}
		}

		choix.sort();
		SortedList<double, Groupe>::iterator 
			groupeChoisi = choix.begin(),
			endChoix = choix.end();
		for ( ; groupeChoisi!=endChoix; ++groupeChoisi) {
			groupeChoisi->jouerAction();
		}
		//*/

		/* Chacun son tour
		for ( ; groupe!=end; ++groupe) {
			Get<Timer>().checkpoint();
			groupe->preparerAction();
			groupe->jouerAction();
			if (!Get<Timer>().checkTime()) {
				break;
			}
		}
		//*/



		effectuerDeplacements();
		if (Get<Timer>().isOver()) {
			cerr << "[Alerte] Time out" << endl;
		}
	}
}

void IA::attaquer(int cibleX, int cibleY) {
	m_joueur.attaquer(cibleX, cibleY);
}

void IA::deplacer(int xFrom, int yFrom, int xTo, int yTo, int nombre) {
	m_deplacements.push_back(Deplacement(xFrom, yFrom, xTo, yTo, nombre));
	zone(xFrom, yFrom).evoluer(m_espece, -nombre);
	zone(xTo, yTo).evoluer(m_espece, nombre);
}

void IA::effectuerDeplacements() {
	//if (m_deplacements.size()<=3) {
		m_joueur.deplacer(m_deplacements);
	//}
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

