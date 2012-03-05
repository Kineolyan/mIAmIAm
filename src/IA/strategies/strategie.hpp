/*
 * strategie.h
 *
 *  Created on: 25 févr. 2012
 *      Author: oliv
 */

#ifndef STRATEGIE_H_
#define STRATEGIE_H_

#include "../situation.h"

template <class Groupe>
class Strategie {
public:
	Strategie() {};
	virtual ~Strategie() {};

	//virtual void enter(Groupe& groupe) =0;
	virtual void execute(Groupe& groupe, Situation& situation) =0;
	//virtual void exit(Groupe& groupe) =0;
};

#endif /* STRATEGIE_H_ */
