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

Noeud::Noeud(int score):
	m_score(score),
	m_fils(),
	m_pere(0)
{}

Noeud::~Noeud()
{}

void Noeud::ajouterFils(Noeud* fils) {
	m_fils.push_back(fils);
}

void Noeud::supprimerFils(Noeud* fils) {
	list<Noeud*>::iterator descendant = fils->m_fils.begin(),
			_end = fils->m_fils.end();
	for ( ; descendant!=_end; ++descendant) {
		fils->supprimerFils(*descendant);
	}

	m_fils.remove(fils);
}

int Noeud::max(int alpha, int beta) {
	cout << "max: "<< alpha << " | " << beta << endl;
	if (m_fils.empty()) {
		cout << "score "<< m_score << endl;
		return m_score;
	}
	else {
		list<Noeud*>::iterator descendant = m_fils.begin(),
			_end = m_fils.end();
		for ( ; descendant!=_end; ++descendant) {
			alpha = tMaximum(alpha, (*descendant)->min(alpha, beta));
			cout << "actualisation alpha = " << alpha << endl;
			if (alpha >= beta) {
				cout << "coupe" << endl;
				return beta;
			}
		}

		return alpha;
	}
}

int Noeud::min(int alpha, int beta) {
	cout << "min: "<< alpha << " | " << beta << endl;
	if (m_fils.empty()) {
		cout << "score "<< m_score << endl;
		return m_score;
	}
	else {
		list<Noeud*>::iterator descendant = m_fils.begin(),
			_end = m_fils.end();
		for ( ; descendant!=_end; ++descendant) {
			beta = tMinimum(beta, (*descendant)->max(alpha, beta));
			cout << "actualisation beta = " << beta << endl;
			if (alpha >= beta) {
				cout << "coupe" << endl;
				return alpha;
			}
		}

		return beta;
	}
}
