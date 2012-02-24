/*
 * gestionnaireNoeuds.cpp
 *
 *  Created on: 24 févr. 2012
 *      Author: oliv
 */

#include "gestionnaireNoeuds.h"

GestionnaireNoeuds::GestionnaireNoeuds():
	m_noeuds(),
	m_noeudSuivant(),
	m_noeudsDisponibles()
{}

GestionnaireNoeuds::~GestionnaireNoeuds()
{}

void GestionnaireNoeuds::init(int taille) {
	m_noeuds.resize(taille);
	m_noeudSuivant = m_noeuds.begin();
}

Noeud* GestionnaireNoeuds::nouveauNoeud() {
	if (m_noeudsDisponibles.empty()) {
		return &(*m_noeudSuivant++);
	}
	else {
		Noeud* noeud = m_noeudsDisponibles.top();
		m_noeudsDisponibles.pop();

		return noeud;
	}
}

void GestionnaireNoeuds::supprimerNoeud(Noeud* noeud) {
	m_noeudsDisponibles.push(noeud);
}
