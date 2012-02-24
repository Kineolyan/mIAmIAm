/*
 * test.cpp
 *
 *  Created on: 23 févr. 2012
 *      Author: oliv
 */

#include <environnement.h>
#include "arbre/noeud.h"
#include "arbre/gestionnaireNoeuds.h"
#include <iostream>

using namespace std;

void afficherResultat(int score) {
	cout << "Resultat: " << score << endl;
}

int main() {
	Create<GestionnaireNoeuds>();
	Get<GestionnaireNoeuds>().init(30);

	Noeud a(Noeud::MAX);
	Noeud *a1, *a2, *a3;

	a.alphaBeta(-1000, 1000);
	// On ajoute le niveau a1 pour l'explorer
	a1 = a.ajouterFils();
	for(;;) {
		// Exploration du niveau a1
		if (a1->ajouterSituation(3)) {
			break;
		}
		if (a1->ajouterSituation(12)) {
			break;
		}
		a1->ajouterSituation(8);
		break;
	}
	if (a1->commit()) {
		afficherResultat(a.score());
		return 1;
	}

	a2 = a.ajouterFils();
	for(;;) {
		if (a2->ajouterSituation(2)) {
			break;
		}
		if (a2->ajouterSituation(4)) {
			break;
		}
		a2->ajouterSituation(6);
		break;
	}
	if (a2->commit()) {
		afficherResultat(a.score());
		return 1;
	}

	a3 = a.ajouterFils();
	for(;;) {
		if (a3->ajouterSituation(14)) {
			break;
		}
		if (a3->ajouterSituation(5)) {
			break;
		}
		a3->ajouterSituation(2);
		break;
	}
	a3->commit();
	afficherResultat(a.score());
	return 1;
}
