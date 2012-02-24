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
	Conteneur::iterator m_noeudSuivant;

	/**
	 * Noeuds disponibles car inutilisés
	 */
	std::stack<Noeud*> m_noeudsDisponibles;

public:
	GestionnaireNoeuds();
	virtual ~GestionnaireNoeuds();

	void init(int taille);

	Noeud* nouveauNoeud();
	void supprimerNoeud(Noeud* noeud);
};

#endif /* GESTIONNAIRENOEUDS_H_ */
