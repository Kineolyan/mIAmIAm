/*
 * ennemi.h
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#ifndef ENNEMI_H_
#define ENNEMI_H_

#include "../jeu/plateau.h"


class Ennemi {
	Case* m_position;

public:
	Ennemi(Case* position);
	Ennemi(Case& position);
	~Ennemi();

	int effectif() const;
	Case* position();
};

#endif /* ENNEMI_H_ */
