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
#include <vector>
#include "../jeu/Client.h"
#include "../jeu/plateau.h"
#include "groupe.h"

class JoueurIA;

class IA {
private:
	typedef std::list<Groupe> Groupes;
	typedef std::list<Case*> Ennemis;
	typedef std::list<Case*> Humains;

	int m_x;
	int m_y;

	JoueurIA& m_joueur;

	Plateau* m_plateau;

	const Espece m_espece;
	const Espece m_especeEnnemie;

	Case* m_cible;

	std::list<Groupe> m_groupes;
	std::list<Case*> m_ennemis;
	std::list<Case*> m_humains;
	
	std::vector<Deplacement> m_deplacements;
	
	void effectuerDeplacements();

public:
	IA(JoueurIA& joueur, Espece espece);
	virtual ~IA();

	void creerPlateau(int largeur, int hauteur);
	Case& zone(int x, int y);
	Plateau& plateau();

	void reset();
	void placer(int x, int y);

	Groupe& ajouterGroupe(int x, int y);
	void supprimerGroupe(int x, int y);
	void separerGroupe(Groupe& groupe, int x, int y, int taille);

	Case& ajouterEnnemi(int x, int y);
	void supprimerEnnemi(int x, int y);

	Case& ajouterHumains(int x, int y);
	void supprimerHumains(int x, int y);

	void update(int x, int y, int h, int v, int l);

	void initialiserCibles();
	Case* choisirCible(const Groupe& groupe);
	void choisirCaseSuivante();
	void jouer();
	void attaquer(int cibleX, int cibleY);
	void deplacer(int fromX, int fromY, int toX, int toY, int nombre);

	void verifierSituation();
};

#endif /* IA_H_ */
