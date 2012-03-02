/*
 * cible.cpp
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#include "cible.h"

Cible::Cible(Groupe* cibleur, Espece espece):
	m_cibleur(cibleur),
	m_espece(espece)
{}

Cible::~Cible()
{}

void Cible::destructionCible() {
	m_cibleur->supprimerCible();
}

/* -- -- */

CibleHumaine::CibleHumaine(Groupe* cibleur, Humain* humain):
	Cible(cibleur, HUMAIN),
	m_cible(humain) {
	m_cible->poursuiviePar(this);
}

CibleHumaine::CibleHumaine(Groupe& cibleur, Humain& humain):
	Cible(&cibleur, HUMAIN),
	m_cible(&humain) {
	m_cible->poursuiviePar(this);
}

int CibleHumaine::effectif() const
{	return m_cible->effectif();	}

Case* CibleHumaine::position()
{	return m_cible->position();	}

void CibleHumaine::annulerCible() {
	m_cible->annulerPoursuite();
}

bool CibleHumaine::verifierCible()
{	return m_espece==m_cible->position()->occupant();	}

/* -- -- */

CibleEnnemie::CibleEnnemie(Groupe* cibleur, Ennemi* ennemi):
	Cible(cibleur, ennemi->position()->occupant()),
	m_cible(ennemi) {
	m_cible->poursuiviePar(this);
}

CibleEnnemie::CibleEnnemie(Groupe& cibleur, Ennemi& ennemi):
	Cible(&cibleur, ennemi.position()->occupant()),
	m_cible(&ennemi) {
	m_cible->poursuiviePar(this);
}

int CibleEnnemie::effectif() const
{	return m_cible->effectif();	}

Case* CibleEnnemie::position()
{	return m_cible->position();	}

void CibleEnnemie::annulerCible() {
	m_cible->annulerPoursuite();
}

bool CibleEnnemie::verifierCible()
{	return m_espece==m_cible->position()->occupant();	}

/* -- -- */

CibleAmie::CibleAmie(Groupe* cibleur, Groupe* amie):
	Cible(cibleur, amie->position().occupant()),
	m_cible(amie) {
	m_cible->poursuiviePar(this);
}

CibleAmie::CibleAmie(Groupe& cibleur, Groupe& amie):
	Cible(&cibleur, amie.position().occupant()),
	m_cible(&amie) {
	m_cible->poursuiviePar(this);
}

int CibleAmie::effectif() const
{	return m_cible->effectif();	}

Case* CibleAmie::position()
{	return &(m_cible->position());	}

void CibleAmie::annulerCible() {
	m_cible->annulerPoursuite();
}

bool CibleAmie::verifierCible()
{	return m_espece==m_cible->position().occupant();	}
