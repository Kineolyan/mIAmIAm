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
		m_plateau(NULL),
		m_positionX(0), m_positionY(0),
		m_partieEnCours(false) {
	if (!m_communication.connected) {
		throw runtime_error("Impossible de se connecter au serveur");
	}
}

Joueur::~Joueur() {
	if (NULL!=m_plateau) {
		delete m_plateau;
	}
}

void Joueur::jouer() {
	int tour = 0;
	string codeAction;
	while (true) {
		cout << "attente du code: ";
		codeAction = lireCommande();
		cout << codeAction << endl;
		if ("END"==codeAction) {
			m_partieEnCours = false;
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
			system("pause");
		}
	}
}

void Joueur::jouerMouvement(int tour) {
	switch(tour) {
	case 1:
		m_communication.deplacer(5,4,5,3,1);
		break;
	case 2:
		m_communication.deplacer(5,3,5,2,1);
		break;
	case 3:
		m_communication.deplacer(5,2,4,2,1);
		break;
	case 4:
		m_communication.deplacer(4,2,3,2,1);
		break;
	case 5:
		m_communication.deplacer(3,2,2,2,1);
		break;

	case 6:
		m_communication.deplacer(5,4,4,4,1);
		break;
	case 7:
		m_communication.deplacer(4,4,3,4,2);
		break;
	case 8:
		m_communication.deplacer(3,4,2,4,2);
		break;

	case 9:
		m_communication.deplacer(2,2,3,3,1);
		break;

	case 10:
		m_communication.attaquer(2,3);
		break;
	default:
		cout << "aucune action de prevue apres" << endl;
	}
}

//void Joueur::jouer() {
//	cout << "attente du code: ";
//	string codeAction;
//	while (true) {
//		codeAction = lireCommande();
//		cout << codeAction << endl;
//		if ("END"==codeAction) {
//			m_partieEnCours = false;
//			codeAction = lireCommande();
//			if ("SET"==codeAction) {
//				reset();
//			}
//			else if ("BYE"==codeAction) {
//				return;
//			}
//			else {
//				throw runtime_error(
//					string("Partie terminee mais reception de commande incorrecte (") + codeAction + ")");
//			}
//		}
//		else if ("UPD"==codeAction) {
//			mettreAJour();
//			m_communication.deplacer(5,4,5,3,1);
//			m_communication.recevoir();
//			system("pause");
//			m_communication.deplacer(5,3,5,2,1);
//			m_communication.recevoir();
//			system("pause");
//			m_communication.deplacer(5,2,4,2,1);
//			m_communication.recevoir();
//			system("pause");
//			m_communication.deplacer(4,2,3,2,1);
//			m_communication.recevoir();
//			system("pause");
//			m_communication.deplacer(3,2,2,2,1);
//			m_communication.recevoir();
//			system("pause");
//
//			m_communication.attaquer(2,3);
//		}
//	}
//}

void Joueur::reset() {
	if (NULL!=m_plateau) {
		delete m_plateau;
	}

	initialiser();
}

void Joueur::creerPlateau(int hauteur, int largeur) {
	try {
		m_plateau = new Plateau(hauteur, largeur);
		cout << "La grille contient " << hauteur << " lignes et "
				<< largeur << " colonnes." << endl;
	}
	catch(const exception& e) {
		throw runtime_error("Impossible de creer le plateau");
	}
}

void Joueur::initialiser() {
	int h = m_communication.lireEntier(),
		l = m_communication.lireEntier();
	creerPlateau(h, l);

	// Placer les maisons ...

	lireCommande("HUM");
	int nbrMaisons = m_communication.lireEntier();
	m_humains.resize(nbrMaisons);

	for(int i=0; i < nbrMaisons; i++){
		int x = m_communication.lireEntier();
		int y = m_communication.lireEntier();
		m_plateau->get(x, y).update(Plateau::Case::HUMAIN, 0);
		m_humains[i] = &(m_plateau->get(x, y));

		cout << " - une maison en (" << x << "," << y << ")" << endl;
	}

	// ... puis notre position initiale
	lireCommande("HME");
	xInitial = m_communication.lireEntier();
	yInitial = m_communication.lireEntier();
	m_groupes.push_back(&(m_plateau.get(xInitial, yInitial)));
}

void Joueur::preparerPartie() {
	m_communication.setNom(m_nom);
	system("pause");

	lireCommande("SET");
	initialiser();
}

void Joueur::mettreAJour() {
	int nbrChangements = m_communication.lireEntier();
	for(int i=0; i < nbrChangements; i++){
		int x = m_communication.lireEntier();
		int y = m_communication.lireEntier();
		int h = m_communication.lireEntier();
		int v = m_communication.lireEntier();
		int l = m_communication.lireEntier();

		m_plateau->get(y, x).update(h, v, l);
		cout << " - la case (" << x << "," << y << ") contient d�sormais "
			<< h << " humains, "<< v << " vampires et " << l << " loups-garous."
			<< endl;
	}
}

string Joueur::lireCommande() {
	return m_communication.lireCommande();
}

void Joueur::lireCommande(const std::string& commandeAttendue) {
	string codeAction = m_communication.lireCommande();
	if (commandeAttendue==codeAction) {
		// Lever une exception ou qqch comme ça
	}
}
