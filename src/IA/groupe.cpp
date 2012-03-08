#include "groupe.h"
#include "joueurIA.h"
#include <vector>

using namespace std;

Groupe::Groupe(IA& ia, Case* zone):
	m_general(ia),
	m_x(zone->x()), m_y(zone->y()),
	m_effectif(zone->nbOccupants()),
	m_xAction(-1), m_yAction(-1),
	m_action(ATTENTE),
	m_enAttente(false),
	m_score(0),
	m_strategie(NULL),
	m_scoreCaseMat(),
	m_historX(NULL),
	m_historY(NULL)
{}

Groupe::Groupe(IA& ia, Case* zone, int taille):
	m_general(ia),
	m_x(zone->x()), m_y(zone->y()),
	m_effectif(taille),
	m_xAction(-1), m_yAction(-1),
	m_action(ATTENTE),
	m_enAttente(false),
	m_score(0),
	m_strategie(NULL),
	m_scoreCaseMat(),
	m_historX(NULL),
	m_historY(NULL)
{}

Groupe::~Groupe()
{}

IA& Groupe::general()
{	return m_general;	}

int Groupe::getHistorX(int t){
	//renvoie la coordonées X, t coups avant
	int len = m_historX.size();
	if (t>=0 && t<len){
		return m_historX[len-t-1];
	}
}


int Groupe::getHistorY(int t){
	//renvoie la coordonées Y, t coups avant
	int len = m_historX.size();
	if (t>=0 && t<len){
		return m_historY[len-t-1];
	}


}

void Groupe::setHistorX(int x){

	std::vector<int>::iterator it;
	it = m_historX.begin ();
	m_historX.insert (it, x);

}
void Groupe::setHistorY(int y){

	std::vector<int>::iterator it;
	it = m_historY.begin ();
	m_historY.insert (it, y);

}

int Groupe::x() const
{	return m_x;	}

int Groupe::y() const
{	return m_y;	}

Case* Groupe::position()
{	return &m_general.zone(m_x, m_y);	}

const Case* Groupe::position() const
{	return &m_general.zone(m_x, m_y);	}

void Groupe::position(int x, int y)
{	m_x = x; m_y = y;	}

Espece Groupe::espece() const
{	return position()->occupant();	}

Espece Groupe::especeEnnemie() const
{	return LOUP==position()->occupant()? VAMPIRE: LOUP;	}

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

void Groupe::setScoreCaseMat(int i, int j, float score){
	m_scoreCaseMat[i][j] = score;
}

void Groupe::augmenterScore(double increment)
{	m_score+= increment;	}

void Groupe::strategie(GameStrategy* strategie)
{	m_strategie = strategie;	}

int Groupe::effectif() const
{	return m_effectif;	}

bool Groupe::pretAAttaquer() const
{	return ATTAQUE==m_action;	}

double Groupe::preparerAction() {
	m_strategie->execute(*this, Situation(m_general.plateau()));

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

void Groupe::attaquer(int xTo, int yTo) {
	cout << "attaque en cours" << endl;

	// Attaquer la cible
	m_general.deplacer(m_x, m_y, xTo, yTo, effectif());

	// Actualisation de la position
	m_x = xTo;
	m_y = yTo;

	// Actualisation des effectifs avec la nouvelle position
	m_effectif = position()->nbOccupants();
}

void Groupe::deplacer(int xTo, int yTo) {
	cout << "deplacement en cours" << endl;
	// Déplacement des unités
	m_general.deplacer(m_x, m_y, xTo, yTo, effectif());

	// Actualisation du groupe en position, l'effectif ne varie pas
	m_x = xTo;
	m_y = yTo;

	m_historX.push_back(m_x);
	m_historY.push_back(m_y);

	for (int i(0);i<m_historX.size();i++){
		cout << m_historX[i] << endl << m_historY[i] << endl;
	}
}

bool Groupe::dejaPasseParCase(Case& place){
	/*for (int i(0);i < 50;i++){
		if (place.x()==getHistorX(i) && place.y()==getHistorY(i)){
			return true;
		}
		else
			return false;
	}*/
	if (m_historX.size()<1){
		return false;
	}

	if (place.x()==m_historX[m_historX.size()-1] && place.y()==m_historY[m_historX.size()-1]){
		return true;
	}
	else
		return false;
}

bool Groupe::dejaPassePar(int x, int y){
	/*for (int i(0);i < 50;i++){
		if (x==getHistorX(i) && y==getHistorY(i)){
			return true;
		}
		else
			return false;
	}*/

	if (m_historX.size()<3){
		return false;
	}

	for (int i (0); i < 3; i++){

		if (x==m_historX[m_historX.size()-i-1] && y==m_historY[m_historX.size()-i-1]){
			return true;
		}
		else
			return false;
	}
}

void Groupe::jouerAction() {
	switch(m_action) {
	case ATTAQUE:
		attaquer(m_xAction, m_yAction);
		break;

	case MOUVEMENT:
		deplacer(m_xAction, m_yAction);
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
	//m_effectif+= groupe.m_effectif;

	m_action = ATTENTE;
}

/**
 * Transfère des unités au groupe passé en argument
 */
void Groupe::transferer(Groupe& groupe, int quantite) {
	// Actualiser les effectifs
	m_effectif-= quantite;
	groupe.m_effectif+= quantite;
}

/**
 * Transfère des unités au groupe passé en argument
 */
Groupe& Groupe::scinder(int xTo, int yTo, int effectif) {
	m_general.deplacer(m_x, m_y, xTo, yTo, effectif);

	// Actualiser les effectifs
	m_effectif-= effectif;

	return m_general.ajouterGroupe(xTo, yTo);
}