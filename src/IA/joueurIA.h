/*
 * joueurIA.h
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#ifndef JOUEURIA_H_
#define JOUEURIA_H_

#include <environnement.h>
#include "../jeu/joueur.h"

class JoueurIA: public Joueur {
protected:
	IA m_cerveau;
	Plateau::Case* m_cible;

	virtual void mettreAJour();
	virtual void reset();
	virtual void initialiser();
	virtual void jouerMouvement(int tour);

public:
	JoueurIA(const std::string, const std::string, const std::string);
	virtual ~JoueurIA();

};

#endif /* JOUEURIA_H_ */
