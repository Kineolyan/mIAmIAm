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

class JoueurIA;

class IA {
private:
	int m_x;
	int m_y;

	JoueurIA& m_joueur;

	Plateau* m_plateau;

	Espece m_espece;
	Espece m_especeEnnemie;

	Plateau::Case* m_cible;

	std::list<Groupe> m_groupes;
	std::list<Plateau::Case*> m_ennemis;
	std::list<Plateau::Case*> m_humains;

public:
	IA(JoueurIA& joueur, Espece espece);
	virtual ~IA();

	void creerPlateau(int largeur, int hauteur);
	inline Plateau::Case& zone(int x, int y);

	void reset();
	void placer(int x, int y);

	void ajouterGroupe(int x, int y, int nombre);
	void ajouterEnnemi(int x, int y, int nombre);
	void ajouterHumains(int x, int y);
	//void supprimerHumains(int x, int y);

	void update(int x, int y, int h, int v, int l);

	void initialiserCibles();
	Case* choisirCible();
	void choisirCaseSuivante();
	void jouer();
};

#endif /* IA_H_ */
