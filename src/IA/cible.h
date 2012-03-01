/*
 * cible.h
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#ifndef CIBLE_H_
#define CIBLE_H_

#include "../jeu/plateau.h"
#include "humain.h"
#include "ennemi.h"
#include "groupe.h"

class Cible {
private:
	Groupe* m_cibleur;

public:
	Cible(Groupe* groupe);
	virtual ~Cible();

	virtual int effectif() const =0;
	virtual Case* position() =0;
	virtual void annulerCible() =0;

	void destructionCible();
};

class CibleHumaine: public Cible {
private:
	Humain* m_cible;

public:
	CibleHumaine(Groupe* groupe, Humain* humain);
	CibleHumaine(Groupe& groupe, Humain& humain);

	int effectif() const;
	Case* position();
	void annulerCible();
};

class CibleEnnemie: public Cible {
private:
	Ennemi* m_cible;

public:
	CibleEnnemie(Groupe* groupe, Ennemi* ennemi);
	CibleEnnemie(Groupe& groupe, Ennemi& ennemi);

	int effectif() const;
	Case* position();
	void annulerCible();
};

class CibleAmie: public Cible {
private:
	Groupe* m_cible;

public:
	CibleAmie(Groupe* groupe, Groupe* cible);
	CibleAmie(Groupe& groupe, Groupe& cible);

	int effectif() const;
	Case* position();
	void annulerCible();
};

#endif /* CIBLE_H_ */
