#ifndef GROUPE_H_
#define GROUPE_H_

#include <environnement.h>
#include "../jeu/plateau.h"
#include "strategie.hpp"

class JoueurIA;
class IA;

class Groupe {
public:
	enum Action { ATTAQUE, MOUVEMENT, ATTENTE, ACTION };

private:
	typedef Strategie<Groupe> GameStrategy;


	IA& m_general;

	int m_x;
	int m_y;
	Case* m_cible;
	int m_actionX;
	int m_actionY;

	Action m_action;
	bool m_enAttente;
	double m_score;

	GameStrategy* m_strategie;

	void choisirCaseSuivante();

public:
	Groupe(IA& ia, Case* zone);
	~Groupe();

	IA& general();

	int x() const;
	int y() const;
	Case& position();
	const Case& position() const;
	void position(int x, int y);

	Case* cible();
	const Case* cible() const;
	void cible(Case* cible);
	void cible(Case& cible);
	void supprimerCible();

	void positionAction(int x, int y);
	Action action() const;
	void action(Action action);
	bool enAttente() const;

	double score() const;
	void score(double score);
	void augmenterScore(double increment);

	void strategie(GameStrategy* strategie);

	int taille() const;
	bool pretAAttaquer() const;

	double preparerAction();
	void jouerAction();
};

#endif // GROUPE_H_
