/*
 * joueurPhysique.h
 *
 *  Created on: 26 janv. 2012
 *      Author: oliv
 */

#ifndef JOUEURPHYSIQUE_H_
#define JOUEURPHYSIQUE_H_

#include <environnement.h>
#include "joueur.h"

class JoueurPhysique: public Joueur {
protected:
	virtual void mettreAJour();
	virtual void initialiser();
	virtual void reset();
	virtual void jouerMouvement(int tour);

public:
	JoueurPhysique(const std::string nom, const std::string hote, const std::string port);
	~JoueurPhysique();
};

#endif /* JOUEURPHYSIQUE_H_ */
