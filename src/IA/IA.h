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

class IA {
private:
	int m_x;
	int m_y;

	Plateau* m_plateau;

	Espece m_espece;
	Espece m_especeEnnemie;

	Plateau::Case* m_cible;

	std::list<Plateau::Case*> m_groupes;
	std::list<Plateau::Case*> m_ennemis;
	std::list<Plateau::Case*> m_humains;

public:
	IA(Espece espece);
	virtual ~IA();

	void creerPlateau(int largeur, int hauteur);
	inline Plateau::Case& zone(int x, int y);

	void reset();
	void placer(int x, int y);

	void ajouterAmis(int x, int y, int nombre);
	void ajouterEnnemis(int x, int y, int nombre);
	void ajouterHumains(int x, int y, int nombre);
	void supprimerHumains(int x, int y);

	void update(int x, int y, int h, int v, int l);

	void initialiserCibles();
	void jouer();
};

#endif /* IA_H_ */
