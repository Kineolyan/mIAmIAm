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
