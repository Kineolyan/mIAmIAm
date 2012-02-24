/*
 * test.cpp
 *
 *  Created on: 23 févr. 2012
 *      Author: oliv
 */

#include "arbre/noeud.h"
#include <iostream>

using namespace std;

void afficherResultat(int score) {
	cout << "Resultat: " << score << endl;
}

int main() {
	Noeud a(Noeud::MAX),
		a1(Noeud::MIN), a2(Noeud::MIN), a3(Noeud::MIN);

	a.alphaBeta(-1000, 1000);
	// On ajoute le niveau a1 pour l'explorer
	a.ajouterFils(&a1);
	for(;;) {
		// Exploration du niveau a1
		if (a1.ajouterSituation(3)) {
			break;
		}
		if (a1.ajouterSituation(12)) {
			break;
		}
		a1.ajouterSituation(8);
		break;
	}
	if (a1.commit()) {
		afficherResultat(a.score());
		return 1;
	}

	a.ajouterFils(&a2);
	for(;;) {
		if (a2.ajouterSituation(2)) {
			break;
		}
		if (a2.ajouterSituation(4)) {
			break;
		}
		a2.ajouterSituation(6);
		break;
	}
	if (a2.commit()) {
		afficherResultat(a.score());
		return 1;
	}

	a.ajouterFils(&a3);
	for(;;) {
		if (a3.ajouterSituation(14)) {
			break;
		}
		if (a3.ajouterSituation(5)) {
			break;
		}
		a3.ajouterSituation(2);
		break;
	}
	a3.commit();
	afficherResultat(a.score());
	return 1;
}
