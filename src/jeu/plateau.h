/*
 * plateau.h
 *
 *  Created on: 24 janv. 2012
 *      Author: oliv
 */

#ifndef PLATEAU_H_
#define PLATEAU_H_

#include <environnement.h>
#include <vector>

enum Espece { VIDE, HUMAIN, VAMPIRE, LOUP };

class Case {
private:
	int m_positionX;
	int m_positionY;
	Espece m_occupant;
	int m_nombre;

public:
	Case();
	Case(int positionX, int positionY, const Espece occupant,
			const int nombre);
	Case(int positionX, int positionY,
			int nbHumains, int nbVampires, int nbLoups);
	Case(const Case& original);

	int x() const;
	int y() const;

	void update(const Espece occupant, const int nombre);
	Espece update(int nbHumains, int nbVampires, int nbLoups);
	void evoluer(const Espece occupant, const int nombre);

	void placer(int x, int y);
	bool estEn(int x, int y) const;

	bool estOccupee() const;
	bool estOccupeePar(Espece espece) const;
	int nbOccupants() const;
	Espece occupant() const;

	void reset();

	const int distance(int x, int y) const;
	const int distance(const Case& zone) const;
	const int distance(const Case* zone) const;
};

class Plateau {
private:
	int m_hauteur;
	int m_largeur;
	std::vector<std::vector<Case> > m_plateau;

public:
	Plateau();
	Plateau(int hauteur, int largeur);

	Case& get(int l, int h);
	bool dansPlateau(int l, int h);

	void redimensionner(int hauteur, int largeur);

	void reset();

	const int distanceMax() const;
};

#endif /* PLATEAU_H_ */
