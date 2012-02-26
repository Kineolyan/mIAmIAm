/*
 * strategieSimple.cpp
 *
 *  Created on: 25 févr. 2012
 *      Author: oliv
 */

#include "strategieSimple.h"
#include "../IA.h"

using namespace std;

StrategieSimple::StrategieSimple()
{}

StrategieSimple::~StrategieSimple()
{}

StrategieSimple* StrategieSimple::instance() {
	static StrategieSimple instance;

	return &instance;
}

void StrategieSimple::choisirAction(Groupe& groupe) {
	Plateau& plateau = groupe.general().plateau();
	Case* cible = groupe.cible();
	int min = plateau.distanceMax()+1, distance,
		x = groupe.x(), y = groupe.y();

	for (int i =-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			if (!(0==i && 0==j) && plateau.dansPlateau(x+i, y+j)) {
				Case& place = plateau.get(x + i, y + j);
				distance = place.distance(cible);
				if (place.estOccupee() && distance < min) {
					min = distance;
					groupe.positionAction(x + i, y + j);
				}
			}
		}
	}

	groupe.action(Groupe::MOUVEMENT);
	groupe.score(1);
}

void StrategieSimple::execute(Groupe& groupe) {
	Case* cible = groupe.cible();

	if (NULL!=cible) {
		if (groupe.enAttente()) {
			groupe.augmenterScore(1);
		}
		else if (1==cible->distance(groupe.position())) {
			groupe.action(Groupe::ATTAQUE);
			groupe.positionAction(cible->x(), cible->y());
			groupe.score(1);
		}
		else {
			choisirAction(groupe);
		}
	}
}
