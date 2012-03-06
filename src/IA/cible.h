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
protected:
	Groupe* m_cibleur;
	const Espece m_espece;

public:
	Cible(Groupe* groupe, Espece espece);
	virtual ~Cible();

	virtual int effectif() const =0;
	virtual Case* position() =0;
	virtual void annuler() =0;
	virtual bool verifier() = 0;

	void destructionCible();
};

template <class Target>
class CibleEspece: public Cible {
private:
	Target* m_cible;

public:
	CibleEspece(Groupe* groupe, Target* humain);
	CibleEspece(Groupe& groupe, Target& humain);

	int effectif() const {
		return m_cible->effectif();
	}
	Case* position() {
		return m_cible->position();
	}
	void annuler() {
		m_cible->annulerPoursuite();
		delete this;
	}
	bool verifier() {
		return m_espece==m_cible->position()->occupant();
	}
};

typedef CibleEspece<Humain> CibleHumaine;
typedef CibleEspece<Ennemi> CibleEnnemie;
typedef CibleEspece<Groupe> CibleAmie;

template<>
inline CibleHumaine::CibleEspece(Groupe* cibleur, Humain* humain):
	Cible(cibleur, HUMAIN),
	m_cible(humain) {
	m_cible->poursuiviePar(this);
}

template<>
inline CibleHumaine::CibleEspece(Groupe& cibleur, Humain& humain):
	Cible(&cibleur, HUMAIN),
	m_cible(&humain) {
	m_cible->poursuiviePar(this);
}

template<>
inline CibleEnnemie::CibleEspece(Groupe* cibleur, Ennemi* cible):
	Cible(cibleur, cible->position()->occupant()),
	m_cible(cible) {
	m_cible->poursuiviePar(this);
}

template<>
inline CibleEnnemie::CibleEspece(Groupe& cibleur, Ennemi& cible):
	Cible(&cibleur, cible.position()->occupant()),
	m_cible(&cible) {
	m_cible->poursuiviePar(this);
}

template<>
inline CibleAmie::CibleEspece(Groupe* cibleur, Groupe* cible):
	Cible(cibleur, cible->position()->occupant()),
	m_cible(cible) {
	m_cible->poursuiviePar(this);
}

template<>
inline CibleAmie::CibleEspece(Groupe& cibleur, Groupe& cible):
	Cible(&cibleur, cible.position()->occupant()),
	m_cible(&cible) {
	m_cible->poursuiviePar(this);
}

#endif /* CIBLE_H_ */
