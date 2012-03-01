/*
 * humain.h
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#ifndef HUMAIN_H_
#define HUMAIN_H_

#include "../jeu/plateau.h"

class Cible;

class Humain {
	Cible* m_viseur;
	Case* m_position;

public:
	Humain(Case* m_position);
	Humain(Case& m_position);
	~Humain();

	int effectif() const;
	Case* position();
	void poursuiviePar(Cible* cible);
	void annulerPoursuite();
	bool estCible() const;
};

#endif /* HUMAIN_H_ */
