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
		int srcX, srcY, destX, destY, nb;
		cout << "<departX> <departY> <destX> <destY> <nombre>:" << endl;
		cin >> srcX >> srcY >> destX >> destY >> nb;
		m_communication.deplacer(srcX, srcY, destX, destY, nb);
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
