/*
 * IA.h
 *
 *  Created on: 27 janv. 2012
 *      Author: oliv
 */

#ifndef IA_H_
#define IA_H_

#include <environnement.h>
#include <list>
#include "../jeu/plateau.h"
#include "groupe.h"

class JoueurIA;

class IA {
private:
	int m_x;
	int m_y;

	JoueurIA& m_joueur;

	Plateau* m_plateau;

	Espece m_espece;
	Espece m_especeEnnemie;

	Case* m_cible;

	std::list<Groupe> m_groupes;
	std::list<Case*> m_ennemis;
	std::list<Case*> m_humains;

public:
	IA(JoueurIA& joueur, Espece espece);
	virtual ~IA();

	void creerPlateau(int largeur, int hauteur);
	Case& zone(int x, int y);
	Plateau& plateau();

	void reset();
	void placer(int x, int y);

	Groupe& ajouterGroupe(int x, int y);
	void ajouterEnnemi(int x, int y);
	Case& ajouterHumains(int x, int y);
	void separerGroupe(Groupe& groupe, int x, int y, int taille);
	//void supprimerHumains(int x, int y);

	void update(int x, int y, int h, int v, int l);

	void initialiserCibles();
	Case* choisirCible(const Groupe& groupe);
	void choisirCaseSuivante();
	void jouer();
	void attaquer(int cibleX, int cibleY);
	void deplacer(int fromX, int fromY, int toX, int toY, int nombre);
};

#endif /* IA_H_ */
