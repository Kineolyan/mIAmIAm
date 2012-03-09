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
#include <vector>
#include "../jeu/plateau.h"

class IA;
class Groupe;

class Situation {
public:
	typedef std::list<Case*> Troupes;

private:
	typedef std::list<Case> Evolutions;

	Troupes m_ennemis;
	Troupes m_amis;
	Troupes m_humains;

	Plateau& m_plateau;
	Evolutions m_evolutions;

	int m_xGroupe;
	int m_yGroupe;
	int m_effectif;
	std::vector<int> m_historX;
	std::vector<int> m_historY;

	const Espece m_espece;
	const Espece m_especeEnnemie;

public:
	Situation(IA& cerveau, Groupe& groupe);
	~Situation();

	int xGroupe();
	int yGroupe();
	int effectifGroupe();

	Espece espece();
	Espece especeEnnemie();

	Troupes& ennemis();
	Troupes& amis();
	Troupes& humains();

	void ajouterDeplacement(Espece espece,
			int xFrom, int yFrom, int xTo, int yTo, int nombre);
	const Evolutions& evolutions() const;
	Case* get(int x, int y);
	bool dansPlateau(int x, int y) const;

	int nbHumainsRestants();
	int nbMaisonsRestantes();
	int nbEnnemis();

	void avancerGroupe(int x, int y);
	bool avancerEnnemis();

	bool dejaPassePar(int x, int y);
	bool dejaPassePar(Case& place);
};

#endif /* SITUATION_H_ */
