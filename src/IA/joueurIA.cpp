/*
 * joueurIA.cpp
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#include "joueurIA.h"

using namespace std;

JoueurIA::JoueurIA(const string nom, const string hote, const string port):
	Joueur(nom, hote, port),
	m_cerveau(*this)
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
	int xInitial = m_communication.lireEntier();
	int yInitial = m_communication.lireEntier();

	// On récupére les positions initiales de tout le monde
	lireCommande("MAP");
	initialiserPositions(xInitial, yInitial);

	// Choix de la première cible, on prend la plus proche
	m_cerveau.ajouterGroupe(xInitial, yInitial);
	m_cerveau.initialiserCibles();
}

void JoueurIA::initialiserPositions(int xInitial, int yInitial) {
	int nbrChangements = m_communication.lireEntier();
	vector<int> X(nbrChangements, 0),
			Y(nbrChangements, 0),
			H(nbrChangements, 0),
			V(nbrChangements, 0),
			L(nbrChangements, 0);
	for(int i=0; i < nbrChangements; i++){
		X[i] = m_communication.lireEntier();
		Y[i] = m_communication.lireEntier();
		H[i] = m_communication.lireEntier();
		V[i] = m_communication.lireEntier();
		L[i] = m_communication.lireEntier();

		if (xInitial==X[i] && yInitial==Y[i]) {
			if (0!=V[i]) {
				m_cerveau.espece(VAMPIRE);
			}
			else if (0!=L[i]) {
				m_cerveau.espece(LOUP);
			}
		}
	}

	// On joue les updates
	for(int i=0; i < nbrChangements; i++){
		m_cerveau.update(X[i], Y[i], H[i], V[i], L[i]);
		cout << " - la case (" << X[i] << ","
			<< X[i] << ") contient d�sormais "
			<< H[i] << " humains, "
			<< V[i] << " vampires et "
			<< L[i] << " loups-garous."
			<< endl;
	}
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

	//m_cerveau.verifierSituation();
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
