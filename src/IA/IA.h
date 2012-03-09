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
#include "humain.h"
#include "ennemi.h"

class JoueurIA;

class IA {
public:
	typedef std::list<Groupe> Groupes;
	typedef std::list<Ennemi> Ennemis;
	typedef std::list<Humain> Humains;
	typedef std::vector<Deplacement> Deplacements;

private:
	JoueurIA& m_joueur;

	Plateau* m_plateau;

	Espece m_espece;
	Espece m_especeEnnemie;

	Groupes m_groupes;
	Ennemis m_ennemis;
	Humains m_humains;
	
	Deplacements m_deplacements;
	
	void effectuerDeplacements();

public:
	IA(JoueurIA& joueur);
	virtual ~IA();

	void espece(Espece espece);
	const Espece espece() const;
	const Espece especeEnnemie() const;

	void creerPlateau(int largeur, int hauteur);
	Case& zone(int x, int y);
	Plateau& plateau();

	void reset();

	Groupe& ajouterGroupe(int x, int y);
	Groupe& ajouterGroupe(int x, int y, int taille);
	void supprimerGroupe(int x, int y);
	void separerGroupe(Groupe& groupe, int x, int y, int taille);
	void fusionnerGroupes(int xGroupe, int yGroupe, int xCible, int yCible);

	Ennemi& ajouterEnnemi(int x, int y);
	void supprimerEnnemi(int x, int y);

	Humain& ajouterHumains(int x, int y);
	void supprimerHumains(int x, int y);
	int nbHumainsRestants();
	int nbMaisonsRestantes();
	int nbEnnemis();

	void update(int x, int y, int h, int v, int l);

	void jouer();
	void attaquer(int cibleX, int cibleY);
	void deplacer(int fromX, int fromY, int toX, int toY, int nombre);

	void verifierSituation();
};

#endif /* IA_H_ */
