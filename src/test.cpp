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

int testCours() {
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

int testExo1() {
	Noeud a(Noeud::MAX);
	Noeud *a1, *a2, *a3;

	a.alphaBeta(-1000, 1000);
	// On ajoute le niveau a1 pour l'explorer
	a1 = a.ajouterFils();
	for(;;) {
		// Exploration du niveau a1
		if (a1->ajouterSituation(-1)) {
			break;
		}

		Noeud *a12 = a1->ajouterFils();
		a12->ajouterSituation(1);
		if (a12->commit()) {
			break;
		}

		Noeud* a13 = a1->ajouterFils();
		a13->ajouterSituation(1);
		a13->commit();
		break;
	}
	if (a1->commit()) {
		afficherResultat(a.score());
		return 1;
	}

	a2 = a.ajouterFils();
	for(;;) {
		Noeud* a21 = a2->ajouterFils();
		a21->ajouterSituation(1);
		if (a21->commit()) {
			break;
		}

		Noeud* a22 = a2->ajouterFils();
		a22->ajouterSituation(1);
		if (a22->commit()) {
			break;
		}
		for(;;) {
			Noeud* a221 = a22->ajouterFils();
			a221->ajouterSituation(-1);
			if (a221->commit()) {
				break;
			}

			Noeud* a222 = a22->ajouterFils();
			a222->ajouterSituation(-1);
			if (a222->commit()) {
				break;
			}
		}
		a22->commit();
		break;
	}
	if (a2->commit()) {
		afficherResultat(a.score());
		return 1;
	}

	a3 = a.ajouterFils();
	for(;;) {
		Noeud *a31 = a3->ajouterFils();
		a31->ajouterSituation(1);
		if (a31->commit()) {
			break;
		}

		Noeud *a32 = a3->ajouterFils();
		a32->ajouterSituation(1);
		if (a32->commit()) {
			break;
		}
		for (;;) {
			Noeud *a321 = a32->ajouterFils();
			a321->ajouterSituation(-1);
			if (a321->commit()) {
				break;
			}

			Noeud* a322 = a32->ajouterFils();
			a322->ajouterSituation(-1);
			a322->commit();
		}
		if (a32->commit()) {
			break;
		}

		Noeud* a33 = a3->ajouterFils();
		Noeud *a331 = a33->ajouterFils();
		a331->ajouterSituation(-1);
		a331->commit();
		a33->commit();
		break;
	}
	a3->commit();
	afficherResultat(a.score());
	return 1;
}

int main() {
	Create<GestionnaireNoeuds>();
	Get<GestionnaireNoeuds>().init(100);

	testExo1();
	return 1;
}
