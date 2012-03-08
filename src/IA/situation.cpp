/*
 * situation.cpp
 *
 *  Created on: 2 mars 2012
 *      Author: oliv
 */

#include "situation.h"
#include <climits>

using namespace std;

Situation::Situation(Plateau& plateau):
	m_plateau(plateau),
	m_evolutions()
{}

Situation::Situation(const Situation& org):
	m_plateau(org.m_plateau),
	m_evolutions(org.m_evolutions)
{}

Situation::~Situation()
{}

void Situation::ajouterDeplacement(Espece espece,
		int xFrom, int yFrom, int xTo, int yTo, int nombre) {
	Evolutions::iterator position = m_evolutions.begin(),
			_end = m_evolutions.end();

	// Evoluer la case précédente
	bool positionTrouvee = false;
	for ( ; position!=_end; ++position) {
		if (position->estEn(xFrom, yFrom)) {
			positionTrouvee = true;
			position->evoluer(espece, -nombre);
		}
	}
	if (!positionTrouvee) {
		Case c = m_plateau.get(xFrom, yFrom);
		c.evoluer(espece, -nombre);
		m_evolutions.push_back(c);
	}

	// Evoluer la case destination
	positionTrouvee = false;
	position = m_evolutions.begin();
	for ( ; position!=_end; ++position) {
		if (position->estEn(xTo, yTo)) {
			positionTrouvee = true;
			position->evoluer(espece, nombre);
		}
	}
	if (!positionTrouvee) {
		Case c = m_plateau.get(xTo, yTo);
		c.evoluer(espece, nombre);
		m_evolutions.push_back(c);
	}
}

const Situation::Evolutions& Situation::evolutions() const
{	return m_evolutions;	}

Case* Situation::get(int x, int y) {
	Evolutions::iterator position = m_evolutions.begin(),
		_end = m_evolutions.end();

	// Evoluer la case précédente
	for ( ; position!=_end; ++position) {
		if (position->estEn(x, y)) {
			return &*position;
		}
	}

	return &m_plateau.get(x, y);
}

bool Situation::dansPlateau(int x, int y) const {
	return m_plateau.dansPlateau(x, y);
}

/* -- Classe de situation pour l'IA -- */

//SituationIA::SituationIA(Espece espece):
//	m_espece(espece),
//	m_especeEnnemie(LOUP==espece? VAMPIRE: LOUP),
//	m_humains(),
//	m_amis(),
//	m_ennemis(),
//	m_monTour(true),
//	m_descendantes()
//{}
//
//SituationIA::~SituationIA()
//{}
//
//void SituationIA::ajouterHumain(int x, int y, int effectif) {
//	m_humains.push_back(JoueurPrevision(
//		Case(x, y, HUMAIN, effectif)
//		));
//}
//
//void SituationIA::ajouterAmi(int x, int y, int effectif) {
//	m_humains.push_back(JoueurPrevision(
//		Case(x, y, m_espece, effectif)
//	));
//}
//
//void SituationIA::ajouterEnnemi(int x, int y, int effectif) {
//	m_humains.push_back(JoueurPrevision(
//		Case(x, y, m_especeEnnemie, effectif)
//	));
//}
//
//void SituationIA::determinerIssue() {
//	int tempsMin = INT_MAX, temps;
//	Amis::iterator ami = m_amis.begin(),
//		_endAmis = m_amis.end();
//	for ( ; ami!=_endAmis; ++ami) {
//		temps = ami->evaluerTempsAction(m_monTour);
//		if (temps < tempsMin) {
//			tempsMin = temps;
//		}
//	}
//	
//	Ennemis::iterator ennemi = m_ennemis.begin(),
//		_endEnnemis = m_ennemis.end();
//	for ( ; ennemi!=_endEnnemis; ++ennemi) {
//		temps = ennemi->evaluerTempsAction(m_monTour);
//		if (temps < tempsMin) {
//			tempsMin = temps;
//		}
//	}
//
//	if (INT_MAX==tempsMin) {
//
//	}
//	else {
//		ami = m_amis.begin();
//		for ( ; ami!=_endAmis; ++ami) {
//			if (ami->avancer(tempsMin)) {
//				;
//			}
//		}
//	
//		ennemi = m_ennemis.begin();
//		for ( ; ennemi!=_endEnnemis; ++ennemi) {
//			if (ennemi->avancer(tempsMin)) {
//				;
//			}
//		}
//	}
//}
//
//void SituationIA::evaluer() {
//	int tempsAmis = INT_MAX, temps;
//	Amis::iterator ami = m_amis.begin(),
//		_endAmis = m_amis.end(),
//		choixAmi = m_amis.end();
//	for ( ; ami!=_endAmis; ++ami) {
//		temps = ami->evaluerTempsAction(m_monTour);
//		if (temps < tempsAmis) {
//			tempsAmis = temps;
//			choixAmi = ami;
//		}
//	}
//	
//	int tempsEnnemis = INT_MAX;
//	Ennemis::iterator ennemi = m_ennemis.begin(),
//		_endEnnemis = m_ennemis.end(),
//		choixEnnemi = m_ennemis.end();
//	for ( ; ennemi!=_endEnnemis; ++ennemi) {
//		temps = ennemi->evaluerTempsAction(m_monTour);
//		if (temps < tempsEnnemis) {
//			tempsEnnemis = temps;
//			choixEnnemi = ennemi;
//		}
//	}
//}
//
//void SituationIA::genererDescendance() {
//	Amis::iterator ami = m_amis.begin(),
//		_endAmis = m_amis.end();
//	for ( ; ami!=_endAmis; ++ami) {
//
//	}
//}


