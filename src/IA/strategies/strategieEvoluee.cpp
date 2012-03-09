/*
 * StrategieEvoluee.cpp
 *
 *  Created on: 25 févr. 2012
 *      Author: oliv
 */

#include "strategieEvoluee.h"
#include "../IA.h"
#include "../../util/timer.h"
#include "../situation.h"
#include "../heuristique.h"

using namespace std;

const int NOMBRE_TOURS_PREVU = 5;

StrategieEvoluee::StrategieEvoluee()
{}

StrategieEvoluee::~StrategieEvoluee()
{}

StrategieEvoluee* StrategieEvoluee::instance() {
	static StrategieEvoluee instance;

	return &instance;
}

void StrategieEvoluee::choisirAction(Groupe& groupe, Situation& situation) {
	int x =situation.xGroupe(), y = situation.yGroupe();
	const Espece especeGroupe = situation.espece();
	const Espece especeEnnemie = situation.especeEnnemie();
	float score = INT_MIN;
	float scoreMax = -10000;

	Racine root;

	// On étudie toutes les situations issues de 8 cases autour
	for (int i =-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			if (groupe.dejaPassePar(x+i,y+j)) {
				//cout<<"deja passee par là"<<endl;
			}
			else if (!(0==i && 0==j) && situation.dansPlateau(x+i, y+j)) {
				// On crée une nouvelle situation de jeu pour le mouvement du groupe
				Situation nouvelleSituation(situation);
				nouvelleSituation.avancerGroupe(x+i, y+j);
				if (nouvelleSituation.avancerEnnemis()) {
					root.ajouterSituation(DOUBLE_MIN);
				}
				else {
					Noeud* n = root.ajouterFils()->ajouterFils();
					prevoirTourSuivant(n, 1, situation);
				}
			}
				
			////score = scoreCase(situation, groupe, place);
			////score = scoreDirection(situation,groupe,place,0.5);
			//score = scoreDirectionDistance(situation,groupe,place);
			////groupe.setScoreCaseMat(i,j,score);

			//if (scoreMax==-10000) {
			//	scoreMax = score;dirX = i;dirY = j;
			//}
				
			//if (score > scoreMax
			//	//&& (VIDE==place.occupant() || especeGroupe==place.occupant())
			//) {
			//	scoreMax = score;dirX = i;dirY = j;
			//}
		}
	}

	// On cherche la meilleure solution
	int dirX(0), dirY(0);
	destinationSolution(situation, groupe, root, dirX, dirY);
	
	// On joue l'action donnée par l'arbre
	Case place = *situation.get(x + dirX, y + dirY);
	groupe.positionAction(x + dirX, y + dirY);

	if (HUMAIN==place.occupant() 
		&& 1==estVulnerablePourGroupe(situation, place)) {
		groupe.action(Groupe::ATTAQUE);
	}
	else if(especeEnnemie==place.occupant() 
		&& 1==estVulnerablePourGroupe(situation, place)) {
		groupe.action(Groupe::ATTAQUE);
	}
	/*else if(especeGroupe==place.occupant()) {
		groupe.action(Groupe::FUSION);
	}*/
	else if(especeGroupe==place.occupant()) {
		groupe.action(Groupe::MOUVEMENT);
	}
	else {
		groupe.action(Groupe::MOUVEMENT);
	}
	
	groupe.score(root.score());
}

bool StrategieEvoluee::prevoirTourSuivant(Noeud* pere, int tour, Situation& situation) {
	if (NOMBRE_TOURS_PREVU-1>tour) {
		int x =situation.xGroupe(), y = situation.yGroupe();

		for (int i =-1; i<2; ++i) {
			for (int j=-1; j<2; ++j) {
				if (situation.dejaPassePar(x + i, y + j)) {
					//cout<< "deja passee par là"<<endl;
				}
				else if (!(0==i && 0==j) && situation.dansPlateau(x+i, y+j)) {
					// On crée une nouvelle situation de jeu pour le mouvement du groupe
					Situation nouvelleSituation(situation);
					nouvelleSituation.avancerGroupe(x+i, y+j);
					if (nouvelleSituation.avancerEnnemis()) {
						pere->ajouterSituation(DOUBLE_MIN);
						break;
					}
					else {
						Noeud *n = pere->ajouterFils()->ajouterFils();

						// On joue le tour suivant
						if (prevoirTourSuivant(n, tour+1, nouvelleSituation)) {
							break;
						}
					}
				}
			}
		}
		return pere->commit();
	}
	else {
		int x =situation.xGroupe(), y = situation.yGroupe();

		for (int i =-1; i<2; ++i) {
			for (int j=-1; j<2; ++j) {
				if (situation.dejaPassePar(x + i, y + j)) {
					//cout<< "deja passee par là"<<endl;
				}
				else if (!(0==i && 0==j) && situation.dansPlateau(x+i, y+j)) {
					Case place = *situation.get(x + i, y + j);
					if (pere->ajouterSituation(
							scoreDirection(situation,place))) {
						break;
					}
				
					////score = scoreCase(situation, groupe, place);
					////score = scoreDirection(situation,groupe,place,0.5);
					//score = scoreDirectionDistance(situation,groupe,place);
					////groupe.setScoreCaseMat(i,j,score);

					//if (scoreMax==-10000) {
					//	scoreMax = score;dirX = i;dirY = j;
					//}
				
					//if (score > scoreMax
					//	//&& (VIDE==place.occupant() || especeGroupe==place.occupant())
					//) {
					//	scoreMax = score;dirX = i;dirY = j;
					//}
				}
			}
		}

		return pere->commit();
	}
}

void StrategieEvoluee::destinationSolution(Situation& situation, Groupe& groupe,
		Racine& racine, int& directionX, int& directionY) {
	Racine::solution s = racine.premiereSolution();
	int x = groupe.x(), y = groupe.y();

	for (int i =-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			if (!groupe.dejaPassePar(x + i, y + j)
					&&!(0==i && 0==j) 
					&& situation.dansPlateau(x+i, y+j)) {
				if (s.estLaMeilleure()) {
					directionX = i;
					directionY = j;
					return;
				}
				else {
					++s;
				}
			}
		}
	}
}

void StrategieEvoluee::execute(Groupe& groupe, Situation& situation) {
	choisirAction(groupe, situation);
}
