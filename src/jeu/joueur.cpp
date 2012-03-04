/*
 * joueur.cpp
 *
 *  Created on: 24 janv. 2012
 *      Author: oliv
 */

#include "joueur.h"

using namespace std;

Joueur::Joueur(const string nom, const string hote, const string port):
		m_nom(nom),
		m_communication(hote, port),
		m_partieEnCours(false) {
	if (!m_communication.connected) {
		throw runtime_error("Impossible de se connecter au serveur");
	}
}

Joueur::~Joueur()
{}

void Joueur::jouer() {
	int tour = 0;
	string codeAction;
	while (true) {
		cout << "attente du code: ";
		codeAction = lireCommande();
		cout << codeAction << endl;
		if ("END"==codeAction) {
			codeAction = lireCommande();
			if ("SET"==codeAction) {
				reset();
			}
			else if ("BYE"==codeAction) {
				cout << "fin du jeu" << endl;
				return;
			}
			else {
				throw runtime_error(
					string("Partie terminee mais reception de commande incorrecte (") + codeAction + ")");
			}
		}
		else if ("UPD"==codeAction) {
			mettreAJour();
			jouerMouvement(++tour);
		}
	}
}

//void Joueur::jouerMouvement(int tour) {
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
//}

void Joueur::preparerPartie() {
	m_communication.setNom(m_nom);

	lireCommande("SET");
	initialiser();
}

/**
 * Lit la commande envoyée par le serveur
 */
string Joueur::lireCommande() {
	return m_communication.lireCommande();
}

/**
 * Tente de lire une commande donnée, envoyée par le serveur
 * Si la commande n'est pas celle attendue, une exception est levée.
 */
void Joueur::lireCommande(const std::string& commandeAttendue) {
	string codeAction = m_communication.lireCommande();
	if (commandeAttendue==codeAction) {
		// Lever une exception ou qqch comme ça
	}
}
