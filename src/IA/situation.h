/*
 * situation.h
 *
 *  Created on: 2 mars 2012
 *      Author: oliv
 */

#ifndef SITUATION_H_
#define SITUATION_H_

#include <environnement.h>
#include <list>
#include "../jeu/plateau.h"

class Situation {
private:
	typedef std::list<Case> Evolutions;

	Plateau& m_plateau;
	Evolutions m_evolutions;

public:
	Situation(Plateau& plateau);
	Situation(const Situation& org);
	~Situation();

	void ajouterDeplacement(Espece espece,
			int xFrom, int yFrom, int xTo, int yTo, int nombre);
	const Evolutions& evolutions() const;
	Case* get(int x, int y);
	bool dansPlateau(int x, int y) const;
};

#endif /* SITUATION_H_ */
