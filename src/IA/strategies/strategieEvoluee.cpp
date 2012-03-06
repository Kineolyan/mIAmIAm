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

StrategieEvoluee::StrategieEvoluee()
{}

StrategieEvoluee::~StrategieEvoluee()
{}

StrategieEvoluee* StrategieEvoluee::instance() {
	static StrategieEvoluee instance;

	return &instance;
}

void StrategieEvoluee::choisirAction(Groupe& groupe, Situation& situation) {
	Plateau& plateau = groupe.general().plateau();
	Case* cible = groupe.cible();
	int x = groupe.x(), y = groupe.y();
	Espece const especeGroupe = groupe.espece(),
		const especeEnnemie = groupe.especeEnnemie();
	double score, scoreMax = -1000;

	for (int i =-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			if (!(0==i && 0==j) && plateau.dansPlateau(x+i, y+j)) {
				Case& place = plateau.get(x + i, y + j);
				score = scoreCase(situation, groupe, &place);
				if (score > scoreMax
					&& (VIDE==place.occupant() || especeGroupe==place.occupant())
				) {
					scoreMax = score;
					groupe.positionAction(x + i, y + j);

					if (HUMAIN==place.occupant() 
						&& 1==EstVulnerablePourGroupe(groupe, &place)) {
						groupe.action(Groupe::ATTAQUE);
					}
					else if(especeEnnemie==place.occupant() 
						&& 1==EstVulnerablePourGroupe(groupe, &place)) {
						groupe.action(Groupe::ATTAQUE);
					}
					else if(especeGroupe==place.occupant()) {
						groupe.action(Groupe::MOUVEMENT);
					}
					else {
						groupe.action(Groupe::MOUVEMENT);
					}
				}
			}
		}
	}

	groupe.score(1);
}

void StrategieEvoluee::execute(Groupe& groupe, Situation& situation) {
	//Case* cible = groupe.cible();

	//if (NULL!=cible) {
		//if (groupe.enAttente()) {
		//	groupe.augmenterScore(1);
		//}
		//else if (1==cible->distance(groupe.position())) {
		//	groupe.action(Groupe::ATTAQUE);
		//	groupe.positionAction(cible->x(), cible->y());
		//	groupe.score(1);
		//}
		//else {
			choisirAction(groupe, situation);
	//	}
	//}
}
