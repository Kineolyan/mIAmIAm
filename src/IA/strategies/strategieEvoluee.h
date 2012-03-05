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

class StrategieEvoluee: public Strategie<Groupe> {
private:
	StrategieEvoluee();
	virtual ~StrategieEvoluee();

	void choisirAction(Groupe& groupe, Situation& situation);

public:
	void execute(Groupe& groupe, Situation& situation);

	static StrategieEvoluee* instance();
};

#endif /* STRATEGIEEVOLUEE_H_ */
