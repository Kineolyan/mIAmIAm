/*
 * gestionnaireNoeuds.h
 *
 *  Created on: 24 févr. 2012
 *      Author: oliv
 */

#ifndef GESTIONNAIRENOEUDS_H_
#define GESTIONNAIRENOEUDS_H_

#include <deque>
#include <stack>
#include "noeud.h"

class GestionnaireNoeuds {
	typedef std::deque<Noeud> Conteneur;

	/**
	 * Ensemble des noeuds alloués par le système
	 */
	Conteneur m_noeuds;
	int m_indexNoeudCourrant;

	int m_facteurTaille;

	/**
	 * Noeuds disponibles car inutilisés
	 */
	std::stack<Noeud*> m_recyclage;

	void agrandir();

	bool estCharge();

public:
	GestionnaireNoeuds();
	virtual ~GestionnaireNoeuds();

	void init(int taille);

	Noeud* nouveauNoeud();
	void supprimerNoeud(Noeud* noeud);
};

#endif /* GESTIONNAIRENOEUDS_H_ */
