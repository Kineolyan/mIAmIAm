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
		int m_positionX;
		int m_positionY;
		Occupant m_occupant;
		int m_nombre;

	public:
		Case();
		Case(int positionX, int positionY, const Occupant occupant,
				const int nombre);

		int x() const;
		int y() const;

		void update(const Occupant occupant, const int nombre);
		Occupant update(int nbHumains, int nbVampires, int nbLoups);

		void placer(int x, int y);
		bool estEn(int x, int y) const;

		bool estOccupeePar(Occupant espece) const;
		int nbOccupants() const;

		void reset();

		const int distance(int x, int y) const;
		const int distance(const Case& zone) const;
		const int distance(const Case* zone) const;
	};

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

typedef Plateau::Case::Occupant Espece;

#endif /* PLATEAU_H_ */
