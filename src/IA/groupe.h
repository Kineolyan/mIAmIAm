#ifndef GROUPE_H_
#define GROUPE_H_

#include <environnement.h>
#include "../jeu/plateau.h"
#include "strategies/strategie.hpp"
#include "situation.h"
#include <vector>

class JoueurIA;
class IA;

class Groupe {
public:
	enum Action { ATTAQUE, MOUVEMENT, ATTENTE, FUSION, ACTION };

private:
	typedef Strategie<Groupe> GameStrategy;

	IA& m_general;

	int m_x;
	int m_y;
	int m_effectif;
	int m_xAction;
	int m_yAction;

	std::vector<int> m_historX;
	std::vector<int> m_historY;

	Action m_action;
	bool m_enAttente;
	bool m_aFusionne;
	double m_score;

	float m_scoreCaseMat[3][3];
	
	GameStrategy* m_strategie;

public:
	Groupe(IA& ia, Case* zone);
	Groupe(IA& ia, Case* zone, int taille);
	~Groupe();

	IA& general();

	int x() const;
	int y() const;
	int getHistorX(int t);
	int getHistorY(int t);
	void setHistorX(int x);
	void setHistorY(int y);
	bool aFusionne() const;
	static bool suppressionSiFusion(const Groupe& groupe);
	Case* position();
	const Case* position() const;
	void position(int x, int y);

	Espece espece() const;
	Espece especeEnnemie() const;

	void positionAction(int x, int y);
	Action action() const;
	void action(Action action);
	bool enAttente() const;

	double score() const;
	void score(double score);
	void augmenterScore(double increment);

	void strategie(GameStrategy* strategie);
	//int EstVulnerablePourGroupe(Case place);
	void setScoreCaseMat(int i, int j, float score);

	int effectif() const;
	bool pretAAttaquer() const;
	bool dejaPassePar(Case& place);
	bool dejaPassePar(int x, int y);

	double preparerAction(Situation& situation);
	void jouerAction();

	void attaquer(int xTo, int yTo);
	void deplacer(int xTo, int yTo);
	/**
	 * Donne un ordre de fusion dans le jeu
	 */
	void fusionner(int xTo, int yTo);

	/**
	 * Fusionne deux groupes ensemble
	 */
	void fusionner(Groupe& groupe);
	void transferer(Groupe& groupe, int quantite);
	Groupe& scinder(int xTo, int yTo, int effectif); 
};

#endif // GROUPE_H_
