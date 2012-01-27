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

class Plateau {
public:
	class Case {
	public:
		enum Occupant { VIDE, HUMAIN, VAMPIRE, LOUP };

	private:
		int positionX;
		int positionY;
		Occupant m_occupant;
		int m_nombre;

	public:
		Case();
		Case(int positionX, int positionY, const Occupant occupant,
				const int nombre);

		void update(const Occupant occupant, const int nombre);
		void update(int nbHumains, int nbVampires, int nbLoups);

		void placer(int x, int y);

		bool estOccupeePar(Occupant espece) const;
		int nbOccupants() const;

		void reset();
	};

private:
	int m_hauteur;
	int m_largeur;
	std::vector<std::vector<Case> > m_plateau;

public:
	Plateau();
	Plateau(int hauteur, int largeur);

	Case& get(int h, int l);

	void redimensionner(int hauteur, int largeur);

	void reset();
};

typedef Plateau::Case::Occupant Espece;

#endif /* PLATEAU_H_ */
