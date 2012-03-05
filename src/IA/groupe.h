#ifndef GROUPE_H_
#define GROUPE_H_

#include <environnement.h>
#include "../jeu/plateau.h"
#include "strategies/strategie.hpp"

class JoueurIA;
class IA;
class Cible;

class Groupe {
public:
	enum Action { ATTAQUE, MOUVEMENT, ATTENTE, ACTION };

private:
	typedef Strategie<Groupe> GameStrategy;

	IA& m_general;

	int m_x;
	int m_y;
	int m_effectif;
	Cible* m_cible;
	int m_xAction;
	int m_yAction;

	Action m_action;
	bool m_enAttente;
	double m_score;

	Cible* m_viseur;

	GameStrategy* m_strategie;

	void choisirCaseSuivante();

public:
	Groupe(IA& ia, Case* zone);
	Groupe(IA& ia, Case* zone, int taille);
	~Groupe();

	IA& general();

	int x() const;
	int y() const;
	Case* position();
	const Case* position() const;
	void position(int x, int y);

	Case* cible();
	const Case* cible() const;
	void cible(Cible* cible);
	void cible(Cible& cible);
	void supprimerCible();

	void positionAction(int x, int y);
	Action action() const;
	void action(Action action);
	bool enAttente() const;

	double score() const;
	void score(double score);
	void augmenterScore(double increment);

	void strategie(GameStrategy* strategie);

	int effectif() const;
	bool pretAAttaquer() const;

	double preparerAction();
	void jouerAction();

	void attaquer(int xTo, int yTo);
	void deplacer(int xTo, int yTo);

	/**
	 * Fusionne deux groupes ensemble
	 */
	void fusionner(Groupe& groupe);
	void transferer(Groupe& groupe, int quantite);
	Groupe& scinder(int xTo, int yTo, int effectif); 

	void poursuiviePar(Cible* cible);
	void annulerPoursuite();
	bool estCible() const;

	Espece espece() const;
	Espece especeEnnemie() const;
};

#endif // GROUPE_H_
