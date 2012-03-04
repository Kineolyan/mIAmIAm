/*
 * joueurPhysique.cpp
 *
 *  Created on: 26 janv. 2012
 *      Author: oliv
 */

#include "joueurPhysique.h"

using namespace std;

JoueurPhysique::JoueurPhysique(
		const string nom, const string hote, const string port):
	Joueur(nom, hote, port)
{}

JoueurPhysique::~JoueurPhysique()
{}

void JoueurPhysique::jouerMouvement(int tour) {
	cout << "Choix de l'action: ";
	string codeAction;
	cin >> codeAction;

	if ("MOV"==codeAction){
		int srcX, srcY, destX, destY, nb, iteration = 4;
		string continuer;
		vector<Deplacement> deplacements;
		deplacements.reserve(3);

		while ((--iteration)>0) {
			cout << "<departX> <departY> <destX> <destY> <nombre>:" << endl;
			cin >> srcX >> srcY >> destX >> destY >> nb;
			deplacements.push_back(Deplacement(srcX, srcY, destX, destY, nb));

			if (iteration>1) {
				cout << "autre mouvement [o/n]:";
				cin >> continuer;
				if ("o"!=continuer && "O"!=continuer) {
					break;
				}
			}
		}
		
		m_communication.deplacer(deplacements);
	}
	else if("ATK"==codeAction){
		int cibleX, cibleY;
		cout << "<cibleX> <cibleY>:" << endl;
		cin >> cibleX >> cibleY;
		m_communication.attaquer(cibleX, cibleY);
	}
	else{
		cout << "Commande non reconnue: " << codeAction << endl;
	}
}

void JoueurPhysique::initialiser() {
	int h = m_communication.lireEntier(),
		l = m_communication.lireEntier();

	// Placer les maisons ...
	lireCommande("HUM");
	int nbrMaisons = m_communication.lireEntier();

	for(int i=0; i < nbrMaisons; i++){
		int x = m_communication.lireEntier();
		int y = m_communication.lireEntier();

		cout << " - une maison en (" << x << "," << y << ")" << endl;
	}

	// ... puis notre position initiale
	lireCommande("HME");
	int x = m_communication.lireEntier();
	int y = m_communication.lireEntier();
}

void JoueurPhysique::mettreAJour() {
	int nbrChangements = m_communication.lireEntier();
	for(int i=0; i < nbrChangements; i++){
		int x = m_communication.lireEntier();
		int y = m_communication.lireEntier();
		int h = m_communication.lireEntier();
		int v = m_communication.lireEntier();
		int l = m_communication.lireEntier();

		cout << " - la case (" << x << "," << y << ") contient d�sormais "
			<< h << " humains, "<< v << " vampires et " << l << " loups-garous."
			<< endl;
	}
}

void JoueurPhysique::reset() {
	initialiser();
}
