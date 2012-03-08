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
	m_recyclage(),
	m_facteurTaille(0)
{}

GestionnaireNoeuds::~GestionnaireNoeuds()
{}

void GestionnaireNoeuds::init(int taille) {
	m_facteurTaille = taille;
	if (m_facteurTaille<10) {
		m_facteurTaille = 10;
	}
	m_noeuds.resize(m_facteurTaille);
	m_noeudSuivant = m_noeuds.begin();
}

Noeud* GestionnaireNoeuds::nouveauNoeud() {
	if (m_recyclage.empty()) {
		Conteneur::iterator noeud = m_noeudSuivant;
		if (m_noeuds.end()==++m_noeudSuivant) {
			--m_noeudSuivant;
			agrandir();
			++m_noeudSuivant;
		}

		return &*noeud;
	}
	else {
		Noeud* noeud = m_recyclage.top();
		m_recyclage.pop();

		return noeud;
	}
}

void GestionnaireNoeuds::supprimerNoeud(Noeud* noeud) {
	m_recyclage.push(noeud);
}

void GestionnaireNoeuds::agrandir() {
	m_noeuds.resize(m_noeuds.size() + m_facteurTaille);
}

bool GestionnaireNoeuds::estCharge()
{	return m_recyclage.size()>=0.75*m_noeuds.size(); }
