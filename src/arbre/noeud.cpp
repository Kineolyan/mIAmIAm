/*
 * noeud.cpp
 *
 *  Created on: 23 févr. 2012
 *      Author: oliv
 */

#include "noeud.h"
#include <fonctions.hpp>
#include <iostream>

using namespace std;

Noeud::Noeud(Noeud::Type type):
	m_type(type),
	m_alpha(),
	m_beta(),
	m_fils(),
	m_pere(0),
	m_situation(),
	m_score()
{}

Noeud::~Noeud()
{}

int Noeud::evaluerSituation(int situation) {
	return situation;
}

void Noeud::alphaBeta(int alpha, int beta) {
	m_alpha = alpha;
	m_beta = beta;
}

void Noeud::ajouterFils(Noeud* fils) {
	m_fils.push_back(fils);
	fils->pere(this);
	fils->alphaBeta(m_alpha, m_beta);
}

void Noeud::pere(Noeud* pere)
{	m_pere = pere;	}

void Noeud::supprimerFils(Noeud* fils) {
	list<Noeud*>::iterator descendant = fils->m_fils.begin(),
			_end = fils->m_fils.end();
	for ( ; descendant!=_end; ++descendant) {
		fils->supprimerFils(*descendant);
	}

	m_fils.remove(fils);
}

int Noeud::max() {
	cout << "max: "<< m_alpha << " | " << m_beta << endl;
	if (m_fils.empty()) {
		cout << "score "<< m_score << endl;
		return m_score;
	}
	else {
		list<Noeud*>::iterator descendant = m_fils.begin(),
			_end = m_fils.end();
		for ( ; descendant!=_end; ++descendant) {
			m_alpha = tMaximum(m_alpha, (*descendant)->min());
			cout << "actualisation m_alpha = " << m_alpha << endl;
			if (m_alpha >= m_beta) {
				cout << "coupe" << endl;
				return m_beta;
			}
		}

		return m_alpha;
	}
}

int Noeud::min() {
	cout << "min: "<< m_alpha << " | " << m_beta << endl;
	if (m_fils.empty()) {
		cout << "score "<< m_score << endl;
		return m_score;
	}
	else {
		list<Noeud*>::iterator descendant = m_fils.begin(),
			_end = m_fils.end();
		for ( ; descendant!=_end; ++descendant) {
			m_beta = tMinimum(m_beta, (*descendant)->max());
			cout << "actualisation m_beta = " << m_beta << endl;
			if (m_alpha >= m_beta) {
				cout << "coupe" << endl;
				return m_alpha;
			}
		}

		return m_beta;
	}
}

/**
 * Etudie une situation à ajouter en feuille de l'arbre et signale une coupe
 * Si la situation est plus intéressante, on la garde en mémoire
 *
 * @param situation: situation de jeu à étudier
 *
 * @return: true s'il y	a une coupe, false si on peut continuer l'exploration du niveau
 */
bool Noeud::ajouterSituation(int situation) {
	int score = evaluerSituation(situation);

	if (MAX==m_type) {
		if (score > m_alpha) {
			m_situation = situation;
			m_alpha = score;

			return (m_alpha >= m_beta);
		}
	}
	else {
		if (score < m_beta) {
			m_situation = situation;
			m_beta = score;

			return (m_alpha >= m_beta);
		}
	}

	return false;
}

/**
 * Renvoie le score du noeud, suivant son type
 *
 * @return: score du noeud
 */
int Noeud::score() const {
	if (MAX==m_type) {
		return (m_alpha >= m_beta)? m_beta: m_alpha;
	}
	else {
		return (m_alpha >= m_beta)? m_alpha: m_beta;
	}
}

/**
 * Met à jour les alpha-beta du noeud et indique une coupe
 *
 * @param score: score renvoyé par le niveau inférieur
 *
 * @return: true s'il y	a une coupe, false si on peut continuer l'exploration du niveau
 */
bool Noeud::update(int score) {
	if (MAX==m_type) {
		m_alpha = tMaximum(m_alpha, score);

		return (m_alpha >= m_beta);
	}
	else {
		m_beta = tMinimum(m_beta, score);

		return (m_alpha >= m_beta);
	}

	return false;
}

/**
 * Informe son parent de l'évolution de la branche
 */
bool Noeud::commit() const {
	return m_pere->update(score());
}
