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
	typedef std::list<Noeud*> ListepFils;

private:
	Type m_type;

	int m_alpha;
	int m_beta;

	ListepFils m_fils;
	Noeud* m_pere;

	int m_situation;
	int m_score;

	int evaluerSituation(int situation);

public:
	Noeud(Type type = MAX);
	virtual ~Noeud();

	void type(Type type = MAX);
	void alphaBeta(int alpha, int beta);

	/**
	 * Ajoute un fils au noeud
	 */
	Noeud* ajouterFils();

	void pere(Noeud* pere);

	/**
	 * Supprime un fils et toute la branche qui en découle
	 */
	void supprimerFils(Noeud* fils);

	/**
	 * Supprime tous les fils du noeud, donc toutes les branches donc ce noeud est
	 * la racine
	 */
	void supprimerDescendance();

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

class Racine: public Noeud {
public:
	Racine(Type type = MAX);
	~Racine();
};

#endif /* NOEUD_H_ */
