/*
 * joueurIA.cpp
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#include "joueurIA.h"

using namespace std;

JoueurIA::JoueurIA(const string nom, const string hote, const string port,
		Espece espece):
	Joueur(nom, hote, port),
	m_cerveau(*this, espece)
{}

JoueurIA::~JoueurIA()
{}

void JoueurIA::reset() {
	m_cerveau.reset();

	initialiser();
}

void JoueurIA::initialiser() {
	int h = m_communication.lireEntier(),
		l = m_communication.lireEntier();
	m_cerveau.creerPlateau(h, l);

	// Placer les maisons ...
	lireCommande("HUM");
	int nbrMaisons = m_communication.lireEntier();

	for(int i=0; i < nbrMaisons; i++){
		int x = m_communication.lireEntier();
		int y = m_communication.lireEntier();
		m_cerveau.ajouterHumains(x, y);

		cout << " - une maison en (" << x << "," << y << ")" << endl;
	}

	// ... puis notre position initiale
	lireCommande("HME");
	int x = m_communication.lireEntier();
	int y = m_communication.lireEntier();
	m_cerveau.ajouterGroupe(x, y);

	// Choix de la première cible, on prend la plus proche
	m_cerveau.initialiserCibles();

	// On récupére les positions initiales de tout le monde
	lireCommande("MAP");
	mettreAJour();
}

void JoueurIA::mettreAJour() {
	int nbrChangements = m_communication.lireEntier();
	for(int i=0; i < nbrChangements; i++){
		int x = m_communication.lireEntier();
		int y = m_communication.lireEntier();
		int h = m_communication.lireEntier();
		int v = m_communication.lireEntier();
		int l = m_communication.lireEntier();

		m_cerveau.update(x, y, h, v, l);
		cout << " - la case (" << x << "," << y << ") contient d�sormais "
			<< h << " humains, "<< v << " vampires et " << l << " loups-garous."
			<< endl;
	}

	m_cerveau.verifierSituation();
}

void JoueurIA::jouerMouvement(int tour) {
	m_cerveau.jouer();
//	switch(tour) {
//	case 1:
//		m_communication.deplacer(5,4,5,3,1);
//		break;
//	case 2:
//		m_communication.deplacer(5,3,5,2,1);
//		break;
//	case 3:
//		m_communication.deplacer(5,2,4,2,1);
//		break;
//	case 4:
//		m_communication.deplacer(4,2,3,2,1);
//		break;
//	case 5:
//		m_communication.deplacer(3,2,2,2,1);
//		break;
//
//	case 6:
//		m_communication.deplacer(5,4,4,4,1);
//		break;
//	case 7:
//		m_communication.deplacer(4,4,3,4,2);
//		break;
//	case 8:
//		m_communication.deplacer(3,4,2,4,2);
//		break;
//
//	case 9:
//		m_communication.deplacer(2,2,3,3,1);
//		break;
//
//	case 10:
//		m_communication.attaquer(2,3);
//		break;
//	default:
//		cout << "aucune action de prevue apres" << endl;
//	}
}

void JoueurIA::attaquer(int x, int y) {
	m_communication.attaquer(x, y);
}

void JoueurIA::deplacer(int fromX, int fromY, int toX, int toY, int nombre) {
	m_communication.deplacer(fromX, fromY, toX, toY, nombre);
}

void JoueurIA::deplacer(const vector<Deplacement>& deplacements) {
	m_communication.deplacer(deplacements);
}
