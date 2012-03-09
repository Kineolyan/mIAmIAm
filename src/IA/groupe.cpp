#include "groupe.h"
#include "joueurIA.h"

using namespace std;

Groupe::Groupe(IA& ia, Case* zone):
	m_general(ia),
	m_x(zone->x()), m_y(zone->y()),
	m_effectif(zone->nbOccupants()),
	m_xAction(0), m_yAction(0),
	m_action(ATTENTE),
	m_enAttente(false),
	m_aFusionne(false),
	m_score(0),
	m_strategie(NULL),
	m_scoreCaseMat(),
	m_historX(),
	m_historY()
{}

Groupe::Groupe(IA& ia, Case* zone, int taille):
	m_general(ia),
	m_x(zone->x()), m_y(zone->y()),
	m_effectif(taille),
	m_xAction(0), m_yAction(0),
	m_action(ATTENTE),
	m_enAttente(false),
	m_aFusionne(false),
	m_score(0),
	m_strategie(NULL),
	m_scoreCaseMat(),
	m_historX(),
	m_historY()
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

	return -1;
}


int Groupe::getHistorY(int t){
	//renvoie la coordonées Y, t coups avant
	int len = m_historY.size();
	if (t>=0 && t<len){
		return m_historY[len-t-1];
	}

	return -1;
}

void Groupe::setHistorX(int x){
	m_historX.push_back(x);
}
void Groupe::setHistorY(int y){
	m_historY.push_back(y);
}

bool Groupe::aFusionne() const
{	return m_aFusionne;	}

bool Groupe::suppressionSiFusion(const Groupe& groupe)
{	return groupe.aFusionne();	}

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

double Groupe::preparerAction(Situation& situation) {
	if (m_action!=ATTENTE) {
		m_strategie->execute(*this, situation);
	}

	switch(m_action) {
	case ATTAQUE:
		cout << "groupe pret a attaquer - " << m_score << "|" 
			<< m_xAction << "-" << m_yAction << "-" << m_effectif << endl;
		break;
	case MOUVEMENT:
		cout << "groupe en deplacement - " << m_score << "|" 
			<< m_xAction << "-" << m_yAction << "-" << m_effectif << endl;
		break;
	case FUSION:
		cout << "fusion de groupe - " << m_score << "|" 
			<< m_xAction << "-" << m_yAction << "-" << m_effectif << endl;
		break;
	case ACTION:
		throw runtime_error("groupe avec cible mais sans ordre");
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
	Espece especeCible = m_general.zone(xTo, yTo).occupant();
	m_general.deplacer(m_x, m_y, xTo, yTo, effectif());
	if (HUMAIN==especeCible) {
		m_general.supprimerHumains(xTo, yTo);
	}
	else {
		m_general.supprimerEnnemi(xTo, yTo);
	}

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

	//for (int i(0); i<m_historX.size(); i++){
	//	cout << m_historX[i] << endl << m_historY[i] << endl;
	//}
}

/**
 * Fusionne deux groupes ensemble
 */
void Groupe::fusionner(int xTo, int yTo) {
	m_general.fusionnerGroupes(m_x, m_y, xTo, yTo);
}

/**
 * Fusionne deux groupes ensemble
 */
void Groupe::fusionner(Groupe& groupe) {
	m_effectif+= groupe.m_effectif;
	m_action = ATTENTE;
}

bool Groupe::dejaPassePar(Case& place){
	/*for (int i(0);i < 50;i++){
		if (place.x()==getHistorX(i) && place.y()==getHistorY(i)){
			return true;
		}
		else
			return false;
	}*/

	int len = m_historX.size();
	if (len<1) {
		return false;
	}

	for (int i (0); i < 5 && i< len; i++){
		if (place.x()==m_historX[len - 1] 
			&& place.y()==m_historY[len - 1]) {
			return true;
		}
	}
	
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

	int len = m_historX.size();
	if (len<1) {
		return false;
	}

	for (int i (0); i < 5 && i< len; i++){
		if (x==m_historX[len - i - 1] 
			&& y==m_historY[len - i - 1]){
			return true;
		}
	}

	return false;
}

void Groupe::jouerAction() {
	switch(m_action) {
	case ATTAQUE:
		attaquer(m_xAction, m_yAction);
		break;

	case MOUVEMENT:
		deplacer(m_xAction, m_yAction);
		break;

	case FUSION:
		fusionner(m_xAction, m_yAction);
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
	m_action = ACTION;
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

	return m_general.ajouterGroupe(xTo, yTo, effectif);
}