/*
 * noeud.h
 *
 *  Created on: 23 févr. 2012
 *      Author: oliv
 */

#ifndef NOEUD_H_
#define NOEUD_H_

#include <list>

class Noeud {
	int m_score;
	std::list<Noeud*> m_fils;
	Noeud* m_pere;

public:
	Noeud(int score = 0);
	virtual ~Noeud();

	/**
	 * Ajoute un fils au noeud
	 */
	void ajouterFils(Noeud* fils);

	/**
	 * Supprime une branche, donc le noeud et ses descendants
	 */
	void supprimerFils(Noeud* fils);

	/**
	 * Renvoie la valeur maximum des fils
	 *
	 * @return: la valeur maximum parmi les fils
	 */
	int max(int alpha, int beta);

	/**
	 * Renvoie la valeur minimum des fils
	 *
	 * @return: la valeur minimum parmi les fils
	 */
	int min(int alpha, int beta);
};

#endif /* NOEUD_H_ */
