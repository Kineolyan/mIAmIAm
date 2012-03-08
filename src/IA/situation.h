/*
 * situation.h
 *
 *  Created on: 2 mars 2012
 *      Author: oliv
 */

#ifndef SITUATION_H_
#define SITUATION_H_

#include <environnement.h>
#include <list>
#include "../jeu/plateau.h"

class Situation {
private:
	typedef std::list<Case> Evolutions;

	Plateau& m_plateau;
	Evolutions m_evolutions;

public:
	Situation(Plateau& plateau);
	Situation(const Situation& org);
	~Situation();

	void ajouterDeplacement(Espece espece,
			int xFrom, int yFrom, int xTo, int yTo, int nombre);
	const Evolutions& evolutions() const;
	Case* get(int x, int y);
	bool dansPlateau(int x, int y) const;
};

//class SituationIA {
//private:
//	typedef std::list<JoueurPrevision> Humains;
//	typedef std::list<JoueurPrevision> Amis;
//	typedef std::list<JoueurPrevision> Ennemis;
//
//	const Espece m_espece;
//	const Espece m_especeEnnemie;
//
//	Humains m_humains;
//	Amis m_amis;
//	Ennemis m_ennemis;
//
//	bool m_monTour;
//
//	std::list<SituationIA> m_descendantes;
//
////public:
////	class iterator {
////
////	};
//
//public:
//	SituationIA(Espece espece);
//	~SituationIA();
//	
//	void ajouterHumain(int x, int y, int effectif);
//	void ajouterAmi(int x, int y, int effectif);
//	void ajouterEnnemi(int x, int y, int effectif);
//
//	void determinerIssue();
//	void evaluer();
//	void genererDescendance();
//};

#endif /* SITUATION_H_ */
