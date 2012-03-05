#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H

#include <environnement.h>
#include "situation.h"
#include "groupe.h"
#include <cmath>

//int nbUnitesADistance(Espece espece,Case* maison, int distance);

//int nbUnitesAutour(Espece espece,Case* maison, int distance);

bool maisonEstVulnerable(Case *maison,Espece espece,int seuil=10);

//int maisonVulnerable(Case *maison,Espece espece,int seuil=10);

//bool maisonEstVulnerable2(Case *maison ,Espece espece,int seuil=10);

//int nbMaisonsVulnerable(Case* maison, Espece espece, int seuil=10);

//float scoreCasePourGroupe1(Groupe* groupe, Case* place);

float scoreCaseEnnemi(Situation& situation, Groupe& groupe,Case* place,float exposant, int distanceSeuil = 10);

//float scoreCaseEnnemi2(Situation& situation, Groupe *groupe,Case* place,float exposant, int distanceSeuil = 10);

float scoreCaseHumain(Situation& situation, Groupe& groupe,Case* place,float exposant, int distanceSeuil = 10);

//float scoreCaseHumain2(Situation& situation, Groupe *groupe,Case* place,float exposant);

float scoreCaseAmi (Situation& situation, Groupe& groupe, Case* place, float exposant, int distanceSeuil=10);

float scoreCase(Situation& situation, Groupe& groupe, Case* place);

int EstVulnerablePourGroupe(Groupe& groupe, Case *place);

int estAvantageuse(Groupe* groupe, Case* place);

//int nbDeDivisionAEnvisager(Groupe* groupe);

#endif // HEURISTIQUE_H
