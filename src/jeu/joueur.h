/*
 * joueur.h
 *
 *  Created on: 24 janv. 2012
 *      Author: oliv
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include <environnement.h>
#include "Client.h"
#include "plateau.h"

class Joueur {
protected:
	std::string m_nom;

	Client m_communication;
	Plateau* m_plateau;

	int m_positionX;
	int m_positionY;

	bool m_partieEnCours;

	std::vector<Case*> m_ennemis;
	std::vector<Case*> m_groupes;
	std::vector<Case*> m_humains;

protected:
	void mettreAJour();
	void initialiser();
	void creerPlateau(int largeur, int hauteur);
	std::string lireCommande();
	void lireCommande(const std::string& commandeAttendue);

	virtual void jouerMouvement(int tour);

public:
	Joueur(const std::string, const std::string, const std::string);
	~Joueur();

	void preparerPartie();
	void jouer();
	void reset();
};

#endif /* JOUEUR_H_ */
