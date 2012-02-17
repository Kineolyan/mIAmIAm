/*
 * joueurIA.h
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#ifndef JOUEURIA_H_
#define JOUEURIA_H_

#include <environnement.h>
#include <vector>
#include "../jeu/Client.h"
#include "../jeu/joueur.h"
#include "../IA/IA.h"

class JoueurIA: public Joueur {
protected:
	IA m_cerveau;

	virtual void mettreAJour();
	virtual void reset();
	virtual void initialiser();
	virtual void jouerMouvement(int tour);

public:
	JoueurIA(const std::string, const std::string, const std::string);
	virtual ~JoueurIA();

	void attaquer(int x, int y);
	void deplacer(int fromX, int frmoY, int toX, int toY, int nombre);
	void deplacer(const std::vector<Deplacement>& deplacements);

};

#endif /* JOUEURIA_H_ */
