#include "groupe.h"
#include "joueurIA.h"
#include "cible.h"

using namespace std;

Groupe::Groupe(IA& ia, Case* zone):
	m_general(ia),
	m_x(zone->x()), m_y(zone->y()),
	m_effectif(zone->nbOccupants()),
	m_cible(NULL),
	m_xAction(-1), m_yAction(-1),
	m_action(ATTENTE),
	m_enAttente(false),
	m_score(0),
	m_strategie(NULL)
{}

Groupe::~Groupe() {
	if (NULL!=m_cible) {
		m_general.annulerCible(m_cible);
	}

//	if (NULL!=m_viseur) {
//		m_viseur->destructionCible();
//	}
}

IA& Groupe::general()
{	return m_general;	}

int Groupe::x() const
{	return m_x;	}

int Groupe::y() const
{	return m_y;	}

Case& Groupe::position()
{	return m_general.zone(m_x, m_y);	}

const Case& Groupe::position() const
{	return m_general.zone(m_x, m_y);	}

void Groupe::position(int x, int y)
{	m_x = x; m_y = y;	}

Case* Groupe::cible()
{	return (NULL!=m_cible)? m_cible->position(): NULL;	}

const Case* Groupe::cible() const
{	return (NULL!=m_cible)? m_cible->position(): NULL;	}

void Groupe::cible(Cible* cible) {
	m_cible = cible;

	if (NULL!=m_cible) {
		m_action = ACTION;
	}
	else {
		m_action = ATTENTE;
	}

	cout << "nouvelle cible: " << cible << endl;
}

void Groupe::cible(Cible& cible)
{	this->cible(&cible);	}

void Groupe::supprimerCible() {
	m_cible = NULL;
}

void Groupe::positionAction(int x, int y)
{	m_xAction = x; m_yAction = y;	}

Groupe::Action Groupe::action() const
{	return m_action;	}

void Groupe::action(Groupe::Action action) {
	m_action = action;
	m_enAttente = true;
}

bool Groupe::enAttente() const
{	return m_enAttente;	}

double Groupe::score() const
{	return m_score;	}

void Groupe::score(double score)
{	m_score = score;	}

void Groupe::augmenterScore(double increment)
{	m_score+= increment;	}

void Groupe::strategie(GameStrategy* strategie)
{	m_strategie = strategie;	}

int Groupe::effectif() const
{	return m_effectif;	}

bool Groupe::pretAAttaquer() const
{	return ATTAQUE==m_action;	}

void Groupe::choisirCaseSuivante() {
//	int min = m_general.plateau().distanceMax(), distance;
//
//	for (int i =-1; i<2; ++i) {
//		for (int j=-1; j<2; ++j) {
//			if (!(0==i && 0==j) && m_general.plateau().dansPlateau(m_x+i, m_y+j)) {
//				Case& place = m_general.zone(m_x+i, m_y+j);
//				distance = place.distance(m_cible);
//				if (place.estOccupee() && distance < min) {
//					min = distance;
//					m_xAction = m_x + i;
//					m_yAction = m_y + j;
//				}
//			}
//		}
//	}
//
//	cout << "preparation mouvement" << endl;
//	m_action = MOUVEMENT;
//	m_score = 1;
}

double Groupe::preparerAction() {
//	if (NULL!=m_cible) {
//		if (m_enAttente) {
//			++m_score;
//		}
//		else if (1==m_cible->distance(m_x, m_y)) {
//			m_action = ATTAQUE;
//			m_enAttente = true;
//			m_score = 1;
//		}
//		else {
//			choisirCaseSuivante();
//		}
//	}
	m_strategie->execute(*this);

	switch(m_action) {
	case ATTAQUE:
		cout << "groupe pret a attaquer - " << m_score << endl;
		break;
	case MOUVEMENT:
		cout << "groupe en deplacement - " << m_score << endl;
		break;
	case ACTION:
		cout << "groupe avec cible mais sans ordre - " << m_score << endl;
		break;
	case ATTENTE:
		cout << "groupe en attente- " << m_score << endl;
		break;
	}
	return m_score;
}

void Groupe::jouerAction() {
	switch(m_action) {
	case ATTAQUE:
		cout << "attaque en cours" << endl;
		// Attaquer la cible
		m_general.deplacer(m_x, m_y, m_xAction, m_yAction, effectif());

		// Actualisation du groupe en effectif et position
		m_x = m_xAction;
		m_y = m_yAction;
		m_effectif+= m_cible->effectif();

		// Choix d'une nouvelle cible
		cout << "choix d'une nouvelle cible" << endl;
		m_general.supprimerCible(m_cible);
		cible(m_general.choisirCible(*this));
		break;

	case MOUVEMENT:
		cout << "deplacement en cours" << endl;
		m_general.deplacer(m_x, m_y, m_xAction, m_yAction, effectif());
		m_x = m_xAction;
		m_y = m_yAction;
		break;

	case ATTENTE:
		cout << "groupe en attente" << endl;
		break;

	default:
		throw runtime_error("Aucun code d'action pour ce groupe");
		break;
	}

	m_score = 0;
	m_enAttente = false;
}

/**
 * Fusionne deux groupes ensemble
 */
void Groupe::fusionner(Groupe& groupe) {
	m_effectif+= groupe.m_effectif;

	m_action = ATTENTE;
}
