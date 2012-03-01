/*
 * ennemi.h
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#ifndef ENNEMI_H_
#define ENNEMI_H_

#include "../jeu/plateau.h"

class Cible;

class Ennemi {
	Cible* m_viseur;
	Case* m_position;

public:
	Ennemi(Case* position);
	Ennemi(Case& position);
	~Ennemi();

	int effectif() const;
	Case* position();
	void poursuiviePar(Cible* cible);
	void annulerPoursuite();
	bool estCible() const;
};

#endif /* ENNEMI_H_ */
