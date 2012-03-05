/*
 * strategieSimple.h
 *
 *  Created on: 25 févr. 2012
 *      Author: oliv
 */

#ifndef STRATEGIESIMPLE_H_
#define STRATEGIESIMPLE_H_

#include "strategie.hpp"
#include "../groupe.h"

class StrategieSimple: public Strategie<Groupe> {
private:
	StrategieSimple();
	virtual ~StrategieSimple();

	void choisirAction(Groupe& groupe);

public:
	void execute(Groupe& groupe, Situation& situation);

	static StrategieSimple* instance();
};

#endif /* STRATEGIESIMPLE_H_ */
