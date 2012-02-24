#include "groupe.h"
#include "joueurIA.h"

using namespace std;

Groupe::Groupe(IA& ia, Plateau& plateau, Case* zone):
	m_cerveau(ia),
	m_plateau(plateau),
	m_x(zone->x()), m_y(zone->y()),
	m_cible(NULL),
	m_actionX(-1), m_actionY(-1),
	m_action(ATTENTE),
	m_enAttente(false),
	m_score(0)
{}

Groupe::~Groupe()
{}

void Groupe::cible(Case* cible) {
	m_cible = cible;
	m_action = (NULL==m_cible)? ATTENTE: ACTION;
	cout << "nouvelle cible: " << cible << endl;
}

void Groupe::cible(Case& cible) {
	this->cible(&cible);
}

Case& Groupe::cible()
{	return *m_cible;	}

const Case& Groupe::cible() const
{	return *m_cible;	}

Case& Groupe::position()
{	return m_cerveau.zone(m_x, m_y);	}

const Case& Groupe::position() const
{	return m_cerveau.zone(m_x, m_y);	}

int Groupe::x() const
{	return m_x;	}

int Groupe::y() const
{	return m_y;	}

int Groupe::taille() const
{	return position().nbOccupants();	}

bool Groupe::pretAAttaquer()
{	return ATTAQUE==m_action;	}

void Groupe::choisirCaseSuivante() {
	int min = m_cerveau.plateau().distanceMax(), distance;

	for (int i =-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			if (!(0==i && 0==j) && m_cerveau.plateau().dansPlateau(m_x+i, m_y+j)) {
				Case& place = m_cerveau.zone(m_x+i, m_y+j);
				distance = place.distance(m_cible);
				if (place.estOccupee() && distance < min) {
					min = distance;
					m_actionX = m_x + i;
					m_actionY = m_y + j;
				}
			}
		}
	}

	cout << "preparation mouvement" << endl;
	m_action = MOUVEMENT;
	m_score = 1;
}

double Groupe::preparerAction() {
	if (NULL!=m_cible) {
		cout << "entree boucle cible" << endl;
		if (m_enAttente) {
			cout << "entree attente" << endl;
			++m_score;
		}
		else if (1==m_cible->distance(m_x, m_y)) {
			cout << "preparation attaque" << endl;
			m_action = ATTAQUE;
			m_enAttente = true;
			m_score = 1;
		}
		else {
			cout << "entree choix case" << endl;
			choisirCaseSuivante();
		}
	}

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
		m_cerveau.deplacer(m_x, m_y, m_cible->x(), m_cible->y(), taille());

		// Déplacement du groupe
		m_x = m_cible->x();
		m_y = m_cible->y();

		// Choix d'une nouvelle cible
		cout << "choix d'une nouvelle cible" << endl;
		cible(m_cerveau.choisirCible(*this));
		break;

	case MOUVEMENT:
		m_cerveau.deplacer(m_x, m_y, m_actionX, m_actionY, taille());
		m_x = m_actionX;
		m_y = m_actionY;
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
