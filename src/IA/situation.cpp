/*
 * situation.cpp
 *
 *  Created on: 2 mars 2012
 *      Author: oliv
 */

#include "situation.h"
#include "IA.h"
#include "groupe.h"

using namespace std;

Situation::Situation(IA& cerveau, Groupe& groupe):
	m_ennemis(),
	m_amis(),
	m_humains(),
	m_plateau(cerveau.plateau()),
	m_evolutions(),
	m_xGroupe(groupe.x()),
	m_yGroupe(groupe.y()),
	m_effectif(groupe.effectif()),
	m_historX(), m_historY(),
	m_espece(groupe.espece()),
	m_especeEnnemie(groupe.especeEnnemie()) {
		// Copie des listes de humains, ennemis, amis
	{
		IA::Ennemis::iterator ennemi = cerveau.ennemis().begin(),
			end = cerveau.ennemis().end();

		for ( ; ennemi!=end; ++ennemi) {
			m_ennemis.push_back(ennemi->position());
		}
	}
	
	{
		IA::Groupes::iterator ami = cerveau.groupes().begin(),
			end = cerveau.groupes().end();

		for ( ; ami!=end; ++ami) {
			m_amis.push_back(ami->position());
		}
	}
	
	{
		IA::Humains::iterator humain = cerveau.humains().begin(),
			end = cerveau.humains().end();


		for ( ; humain!=end; ++humain) {
			m_humains.push_back(humain->position());
		}
	}

	for (int t = 4; t>=0; --t) {
		m_historX.push_back(groupe.getHistorX(t));
		m_historY.push_back(groupe.getHistorY(t));
	}
}

Situation::~Situation()
{}

int Situation::xGroupe()
{	return m_xGroupe;	}

int Situation::yGroupe()
{	return m_yGroupe;	}

int Situation::effectifGroupe()
{	return m_effectif;	}

Espece Situation::espece()
{	return m_espece;	}

Espece Situation::especeEnnemie()
{	return m_especeEnnemie;	}

Situation::Troupes& Situation::ennemis()
{	return m_ennemis;	}

Situation::Troupes& Situation::amis()
{	return m_amis;	}

Situation::Troupes& Situation::humains()
{	return m_humains;	}

void Situation::ajouterDeplacement(Espece espece,
		int xFrom, int yFrom, int xTo, int yTo, int nombre) {
	Evolutions::iterator position = m_evolutions.begin(),
			_end = m_evolutions.end();

	// Evoluer la case précédente
	bool positionTrouvee = false;
	for ( ; position!=_end; ++position) {
		if (position->estEn(xFrom, yFrom)) {
			positionTrouvee = true;
			position->evoluer(espece, -nombre);
		}
	}
	if (!positionTrouvee) {
		Case c = m_plateau.get(xFrom, yFrom);
		c.evoluer(espece, -nombre);
		m_evolutions.push_back(c);
	}

	// Evoluer la case destination
	positionTrouvee = false;
	position = m_evolutions.begin();
	for ( ; position!=_end; ++position) {
		if (position->estEn(xTo, yTo)) {
			positionTrouvee = true;
			position->evoluer(espece, nombre);
		}
	}
	if (!positionTrouvee) {
		Case c = m_plateau.get(xTo, yTo);
		c.evoluer(espece, nombre);
		m_evolutions.push_back(c);
	}
}

Case* Situation::get(int x, int y) {
	Evolutions::iterator position = m_evolutions.begin(),
		_end = m_evolutions.end();

	// Evoluer la case précédente
	for ( ; position!=_end; ++position) {
		if (position->estEn(x, y)) {
			return &*position;
		}
	}

	return &m_plateau.get(x, y);
}

bool Situation::dansPlateau(int x, int y) const {
	return m_plateau.dansPlateau(x, y);
}

void Situation::avancerGroupe(int x, int y) {
	ajouterDeplacement(m_espece, m_xGroupe, m_yGroupe, x, y , m_effectif);
	m_effectif = get(x, y)->nbOccupants();
	m_historX.push_back(x);
	m_historY.push_back(y);
}

bool Situation::avancerEnnemis() {
	Troupes::iterator ennemi = m_ennemis.begin(),
		endEnnemi = m_ennemis.end();
	for ( ; ennemi!=endEnnemi; ++ennemi) {
		int distanceMax = INT_MAX, xDest = 0, yDest = 0;

		Troupes::iterator troupe = m_amis.begin(),
			end = m_amis.end();
		for ( ; troupe!=end; ++troupe) {
			int distance = (*ennemi)->distance(*troupe);
			if (distance < distanceMax) {
				xDest = (*troupe)->x();
				yDest = (*troupe)->y();
			}
		}

		troupe = m_humains.begin();
		end = m_humains.end();
		for ( ; troupe!=end; ++troupe) {
			int distance = (*ennemi)->distance(*troupe);
			if (distance < distanceMax) {
				xDest = (*troupe)->x();
				yDest = (*troupe)->y();
			}
		}
		
		xDest-= (*ennemi)->x();
		if (0!=xDest) {
			xDest/= vabs(xDest);
		}

		yDest-= (*ennemi)->y();
		if (0!=yDest) {
			yDest/= vabs(yDest);
		}

		if (m_xGroupe==xDest && m_yGroupe==yDest) {
			return true;
		}
		else {
			ajouterDeplacement(m_especeEnnemie, (*ennemi)->x(), (*ennemi)->y(),
				xDest, yDest, (*ennemi)->nbOccupants());
			return false;
		}

	}
}

int Situation::nbHumainsRestants() {
	int nbTotal = 0;
	Troupes::iterator hum = m_humains.begin(),
		end = m_humains.end();
	for ( ; hum!=end; ++hum){
		nbTotal += (*hum)->nbOccupants();
	}

	return nbTotal;
}
int Situation::nbMaisonsRestantes()
{	return m_humains.size();	}

int Situation::nbEnnemis(){
	int nbTotal = 0;
	list<Case*>::iterator ennemi = m_ennemis.begin(),
	
		end = m_ennemis.end();
	for ( ; ennemi!=end; ++ennemi){
		nbTotal += (*ennemi)->nbOccupants();
	}
	
	return nbTotal;
}

bool Situation::dejaPassePar(int x, int y) {
	int len = m_historX.size();
	for (int t = 0; t<len && t<5; ++t) {
		if (x==m_historX[len-1-t] && y==m_historY[len-1-t]) {
			return true;
		}
	}

	return false;
}

bool Situation::dejaPassePar(Case& place)
{	return dejaPassePar(place.x(), place.y());	}


