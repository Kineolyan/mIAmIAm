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
public:
	enum Type { MAX, MIN };

private:
	Type m_type;

	int m_alpha;
	int m_beta;

	std::list<Noeud*> m_fils;
	Noeud* m_pere;

	int m_situation;
	int m_score;

	int evaluerSituation(int situation);

public:
	Noeud();
	Noeud(Type type);
	virtual ~Noeud();

	void type(Type type);
	void alphaBeta(int alpha, int beta);

	/**
	 * Ajoute un fils au noeud
	 */
	Noeud* ajouterFils();

	void pere(Noeud* pere);

	/**
	 * Supprime une branche, donc le noeud et ses descendants
	 */
	void supprimerFils(Noeud* fils);

	/**
	 * Renvoie la valeur maximum des fils
	 *
	 * @return: la valeur maximum parmi les fils
	 */
	int max();

	/**
	 * Renvoie la valeur minimum des fils
	 *
	 * @return: la valeur minimum parmi les fils
	 */
	int min();

	bool ajouterSituation(int situation);

	int score() const;

	bool update(int score);

	bool commit() const;
};

#endif /* NOEUD_H_ */
