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

float scoreCaseEnnemi(Situation& situation, Groupe& groupe,Case& place,float exposant, int distanceSeuil = 10);

//float scoreCaseEnnemi2(Situation& situation, Groupe *groupe,Case* place,float exposant, int distanceSeuil = 10);

float scoreCaseHumain(Situation& situation, Groupe& groupe,Case& place,float exposant, int distanceSeuil = 10);

//float scoreCaseHumain2(Situation& situation, Groupe *groupe,Case* place,float exposant);

float scoreCaseAmi (Situation& situation, Groupe& groupe, Case& place, float exposant, int distanceSeuil=10);

float scoreCaseUrgence(Situation& situation, Groupe& groupe, Case& place,float exposant, int distanceSeuil);

float scoreCase(Situation& situation, Groupe& groupe, Case& place);

float scoreDirection(Situation& situation, Groupe& groupe, Case& place,float param=2);

float scoreDirectionDistance(Situation& situation, Groupe& groupe, Case& place, int distance=3);

float scoreDejaPasse(Situation& situation, Groupe& groupe, Case& place,int distance =2);

int estVulnerablePourGroupe(Situation& situation, Groupe& groupe, Case& place);

int estAvantageuse(Groupe* groupe, Case* place);

//int nbDeDivisionAEnvisager(Groupe* groupe);

float parameEnnemi(Groupe& groupe);
float parameHumain(Groupe& groupe);
float parameAmi(Situation& situation, Groupe& groupe);
float parameVulne(Situation& situation, Groupe& groupe);

#endif // HEURISTIQUE_H
