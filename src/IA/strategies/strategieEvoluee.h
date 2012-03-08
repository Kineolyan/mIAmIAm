/*
 * strategieSimple.h
 *
 *  Created on: 25 févr. 2012
 *      Author: oliv
 */

#ifndef STRATEGIEEVOLUEE_H_
#define STRATEGIEEVOLUEE_H_

#include "strategie.hpp"
#include "../groupe.h"
#include "../../arbre/noeud.h"

class StrategieEvoluee: public Strategie<Groupe> {
private:
	StrategieEvoluee();
	virtual ~StrategieEvoluee();

	void choisirAction(Groupe& groupe, Situation& situation);
	bool prevoirTourSuivant(Noeud* pere, int tour, Groupe& groupe, 
		Situation& situation);
	void destinationSolution(Situation& situation, Groupe& groupe,
		Racine& racine, int& directionX, int directionY);

public:
	void execute(Groupe& groupe, Situation& situation);

	static StrategieEvoluee* instance();
};

#endif /* STRATEGIEEVOLUEE_H_ */
