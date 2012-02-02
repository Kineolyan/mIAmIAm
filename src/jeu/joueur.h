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

	bool m_partieEnCours;

protected:
	virtual void mettreAJour() =0;
	virtual void initialiser() =0;
	virtual void reset() =0;

	std::string lireCommande();
	void lireCommande(const std::string& commandeAttendue);

	virtual void jouerMouvement(int tour) =0;

public:
	Joueur(const std::string, const std::string, const std::string);
	~Joueur();

	void preparerPartie();
	void jouer();
};

#endif /* JOUEUR_H_ */
