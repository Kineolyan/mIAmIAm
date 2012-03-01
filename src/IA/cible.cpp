/*
 * cible.cpp
 *
 *  Created on: 1 mars 2012
 *      Author: oliv
 */

#include "cible.h"

Cible::Cible(Groupe* cibleur):
	m_cibleur(cibleur)
{}

Cible::~Cible()
{}

void Cible::destructionCible() {
	m_cibleur->supprimerCible();
}

/* -- -- */

CibleHumaine::CibleHumaine(Groupe* cibleur, Humain* humain):
	Cible(cibleur),
	m_cible(humain) {
	m_cible->poursuiviePar(this);
}

CibleHumaine::CibleHumaine(Groupe& cibleur, Humain& humain):
	Cible(&cibleur),
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

/* -- -- */

CibleEnnemie::CibleEnnemie(Groupe* cibleur, Ennemi* ennemi):
	Cible(cibleur),
	m_cible(ennemi) {
	m_cible->poursuiviePar(this);
}

CibleEnnemie::CibleEnnemie(Groupe& cibleur, Ennemi& ennemi):
	Cible(&cibleur),
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

/* -- -- */

CibleAmie::CibleAmie(Groupe* cibleur, Groupe* groupe):
	Cible(cibleur),
	m_cible(groupe) {
	//m_cible->poursuiviePar(this);
}

CibleAmie::CibleAmie(Groupe& cibleur, Groupe& groupe):
	Cible(&cibleur),
	m_cible(&groupe) {
	//m_cible->poursuiviePar(this);
}

int CibleAmie::effectif() const
{	return m_cible->effectif();	}

Case* CibleAmie::position()
{	return &(m_cible->position());	}

void CibleAmie::annulerCible() {}
