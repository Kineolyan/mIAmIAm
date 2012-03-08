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

protected:
	Type m_type;

	double m_alpha;
	double m_beta;

	ListepFils m_fils;
	Noeud* m_pere;

	double m_situation;
	double m_score;

public:
	Noeud(Type type = MAX);
	virtual ~Noeud();

	void type(Type type = MAX);
	void alphaBeta(double alpha, double beta);

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

	///**
	// * Renvoie la valeur maximum des fils
	// *
	// * @return: la valeur maximum parmi les fils
	// */
	//int max();

	///**
	// * Renvoie la valeur minimum des fils
	// *
	// * @return: la valeur minimum parmi les fils
	// */
	//int min();

	bool ajouterSituation(double situation);

	double score() const;

	bool update(double score);

	bool commit() const;
};

class Racine: public Noeud {
private:
	typedef ListepFils::iterator Iterator;

public:
	class solution {
	private:
		Iterator m_element;
		double m_scoreMax;

	public:
		solution(const Iterator& element, double scoreMax):
			m_element(element), m_scoreMax(scoreMax) {}

		solution(const solution& position):
			m_element(position.m_element), 
			m_scoreMax(position.m_scoreMax) {}

		solution& operator++()
		{	++m_element; return *this;	}

		solution operator++(int)
		{	solution tmp(*this); operator++(); return tmp;	}

		bool operator==(const solution& rhs) const
		{	return m_element==rhs.m_element;	}

		bool operator!=(const solution& rhs) const
		{	return m_element!=rhs.m_element;	}

		Noeud& operator*()
		{	return **m_element;	}

		Noeud* operator->()
		{	return *m_element;	}

		bool estLaMeilleure()
		{	return m_scoreMax==(*m_element)->score();	}
	};

	Racine(Type type = MAX);
	~Racine();

	solution premiereSolution();
};

#endif /* NOEUD_H_ */
