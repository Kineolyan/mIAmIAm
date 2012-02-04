#ifndef GROUPE_H_
#define GROUPE_H_

#include <environnement.h>
#include "../jeu/plateau.h"

class JoueurIA;
class IA;

class Groupe {
private:
	enum Etat { ATTAQUE, MOUVEMENT, ATTENTE, ACTION };

	IA& m_cerveau;
	Plateau& m_plateau;

	int m_x;
	int m_y;
	Case* m_cible;
	int m_actionX;
	int m_actionY;

	Etat m_action;
	bool m_enAttente;
	double m_score;

	void choisirCaseSuivante();

public:
	Groupe(IA& ia, Plateau& plateau, Case* zone);
	~Groupe();

	int x() const;
	int y() const;
	int taille() const;

	Case& position();
	const Case& position() const;
	void cible(Case* cible);
	void cible(Case& cible);
	Case& cible();
	const Case& cible() const;
	bool pretAAttaquer();

	int preparerAction();
	void jouerAction();
};

#endif // GROUPE_H_
