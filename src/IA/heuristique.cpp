#include "heuristique.h"
#include "IA.h"
#include "groupe.h"

using namespace std;

//int nbDeCoupAvantInvasion(Espece espece, Case *maison){
//
//    int nbGroup = IA.m_groupes.size();  // nombre de groupe de l'espèce
//    int posX[nbGroup];                  // liste des positions X des groupes
//    int posY[nbGroup];                  // liste des positions Y des groupes
//    int dist[nbGroup];                   // listes des distances maison-groupe
//
//    if (IA.m_espece == espece){
//        for (int i(0); i<IA.m_groupes.size();i++){
//            posX[i] = IA.m_groupes[i].m_x;
//            posY[i] = IA.m_groupes[].m_y;
//            maison.distance(IA.m_groupes[i]);
//    // ensuite on peut classer cette liste en fonction de la distance
//    }
//    }
//}

//int nbUnitesADistance(Espece espece,Case* maison, int distance){
//
//// Calcul le nombre d'unité qui sont à distance cases de la maison (ou n'importe quelle autre case)
////
//
//    int x = maison->x();
//    int y = maison->y();
//    int d = distance;
//    int nbUnit = 0;
//
//// TODO : vérifier que ça ne sort pas du plateau
//
//    for (int i(x-d);i<x+d+1;i++){
//        if (plateau.get(i,y-d).occupant()== espece){
//            nbUnit += plateau.get(i,y-d).nbOccupants();
//        }
//        if (plateau.get(i,y-d).occupant()== espece){
//            nbUnit += plateau.get(i,y-d).nbOccupants();
//        }
//    }
//
//    for (int j(y-d+1);j<y+d;j++){
//        if (IA.plateau().get(x-d,j).occupant()== espece){
//            nbUnit += IA.plateau().get(x-d,j).nbOccupants();
//        }
//        if (IA.plateau().get(x-d,j).occupant()== espece){
//            nbUnit += IA.plateau().get(x-d,j).nbOccupants();
//        }
//    }
//
//    return nbUnit;
//
//}



//int nbUnitesAutour(Espece espece,Case* maison, int distance){
////retourne le nombre d'unité
//
//
//    int x = maison->x();
//    int y = maison->y();
//    int d = distance;
//    int nbUnit = 0;
//
//    for (int i(x-d);i<x+d+1;i++){
//        for (int j(y-d);j<y+d+1;j++){
//
//            if (Plateau.dansPlateau(i,j)){
//                if (IA.plateau().get(i,j).occupant()== espece){
//                nbUnit += IA.plateau().get(i,j).nbOccupants();
//                }
//            }
//        }
//    }
//
//    return nbUnit;
//
//}





//bool maisonEstVulnerable(Case *maison,Espece espece,int seuil){
//
//    // renvoie true si la maison est vulnérable (on impose un seuil de 10 cases par exemple)
//
//    int x = maison->x();
//    int y = maison->y();
//    int nbHumains = maison->nbOccupants();
//
//    int k = 0;
//    bool superiorite = false;
//
//    while (superiorite == false){
//        k++;
//        if (nbHumains <=nbUnitesAutour(espece,maison,k)){
//            superiorite = true;
//        }
//        if (k==seuil){
//            return false;
//        }
//    }
//
//    return superiorite;
//
//}

//int maisonVulnerable(Case *maison,Espece espece,int seuil){
//
//    // renvoie le nombre de coup avant conquête
//    //et 0 si elle n'est pas envahissable en moins de seuil(int) coup
//
//    int x = maison->x();
//    int y = maison->y();
//    int nbHumains = maison->nbOccupants();
//	int k = 0;
//
//    while (k<seuil+1){
//        k++;
//        if (nbHumains <=nbUnitesAutour(espece,maison,k)){
//            return k;
//        }
//    }
//    return 0;
//}


//bool maisonEstVulnerable2(Case *maison ,Espece espece,int seuil=10){
//
//    /*Ici on regarde quelle espèce est favorite pour conquérir la maison
//    TODO : améliorer cette fonction en calculant si, même après conquête, le groupe qui a convertit
//    les humains est en supériorité numérique.
//    */
//
//    if (maison->occupant()!=HUMAIN){
//        return false;
//    }
//
//    int nbHumain       = maison->nbOccupants();
//    int nbDeCoupEspece = maisonVulnerable(maison,IA.espece(),seuil);
//    int nbDeCoupEnnemi = maisonVulnerable(maison,IA.especeEnnemi(),seuil);
//
//    if (nbDeCoupEspece>nbDeCoupEnnemi){
//        return false;
//    }
//
//    else{
//        return true
//    }
//}



int nbMaisonsVulnerable(Case* maison, Espece espece, int seuil){
// retourne le nombre de maisons vulnérables pour espece

	return 1;
}





//float scoreCasePourGroupe1(Groupe* groupe, Case* place){
//
//    /*on va calculer : le nombre d'ennemi autour, le nombre d'humain autour (et le nombre d'unités autour)
//      on choisit des paramètres qu'il faudra modifier pour optimiser le jeu.
//      On a définit trois fonctions ci-dessous scoreCaseEnnemi,scoreCaseHumain et scoreCaseAmi
//
//      Chaque case aura un score pour :
//      - estimer où aller :
//      - calculer comment y aller (trouver le chemin qui optimise la somme des scores des cases parcourues
//
//      On pourra ensuite créer plusieurs fonctions scoreCasePourGroupe1() adapté à un moment de la partie
//    */
//
//    float paramEnnemi    = -2;
//    float exposantEnnemi = 0.5;
//
//    float paramHumain    = 2;
//    float exposantHumain = 0.5;
//
//    float paramAmi       = 1;
//    float exposantAmi    = 0.5;
//
//    float score = 0;
//
//    score += paramEnnemi * scoreCaseEnnemi(groupe,place,exposantEnnemi);
//    score += paramHumain * scoreCaseHumain(groupe,place,exposantHumain);
//    score += paramAmi    * scoreCaseAmi(groupe,place,exposantAmi);
//
//    return score;
//}



float scoreCaseEnnemi(Situation& situation,
	Groupe& groupe,Case* place,float exposant, int distanceSeuil){

    // somme(nbOccupant/distance^exposant) sur toutes les cases ennemis < distanceSeuil


    int x = place->x();
    int y = place->y();
    int d = distanceSeuil;
    float score = 0;
	Espece especeEnnemie = groupe.especeEnnemie();

    for (int i(x-d);i<x+d+1;i++){
        for (int j(y-d);j<y+d+1;j++){

            if (situation.dansPlateau(i,j)){
                if (situation.get(i,j)->occupant()== especeEnnemie){
                    int distance = tMaximum(vabs(i-x), vabs(j-y));
                    score += situation.get(i,j)->nbOccupants()/
						pow(distance, exposant);
                }
            }
        }
    }
    return score;
}

//float scoreCaseEnnemi2(Groupe *groupe,Case* place,float exposant, int distanceSeuil = 10){
//
//
//    // deuxieme façon de calculer le score, qui est peut-être plus rapide
//    // somme(nbOccupant/distance^exposant) sur toutes les cases ennemis du vecteur m_ennemis
//
//
//    int x = place->m_positionX;
//    int y = place->m_positionY;
//    int d = distanceSeuil;
//    float score = 0;
//
//    Ennemis::iterator ennemi = m_ennemis.begin(),
//                    end = m_ennemis.end(),
//    for ( ; ennemi!=end; ++ennemi) {
//        int distance = place->distance(ennemi.position());
//        score += ennemi.position().nbOccupant()/(distance*exposant);
//    }
//
//    return score;
//}

float scoreCaseHumain(Situation& situation,
	Groupe& groupe,Case* place,float exposant, int distanceSeuil){

    // somme(nbOccupant/distance^exposant) sur toutes les cases humaines<distanceSeuil

    int x = place->x();
    int y = place->y();
    int d = distanceSeuil;
    float score = 0;

    for (int i(x-d);i<x+d+1;i++){
        for (int j(y-d);j<y+d+1;j++){
            if (situation.dansPlateau(i,j)){
                if (situation.get(i,j)->occupant()== HUMAIN){
                    int distance = tMaximum(vabs(i-x), vabs(j-y));
                    score += situation.get(i,j)->nbOccupants()/
						pow(distance, exposant);
                }
            }
        }
    }

    return score;
}

//float scoreCaseHumain2(Groupe *groupe,Case* place,float exposant){
//
//    // somme(nbOccupant/distance^exposant) sur toutes les cases humaines<distanceSeuil
//
//    int x = place->m_positionX;
//    int y = place->m_positionY;
//    float score = 0;
//
//    Humains::iterator maison = m_humains.begin(),
//                    end = m_humains.end(),
//    for ( ; maison!=end; ++maison) {
//        int distance = place->distance(maison.position());
//        score += maison.position().nbOccupant()/(distance*exposant);
//    }
//
//    return score;
//}

float scoreCaseAmi (Situation& situation, 
	Groupe& groupe, Case* place, float exposant, int distanceSeuil){

    // somme(nbOccupant/distance^exposant) sur toutes les cases amis < distanceSeuil


    int x = place->x();
    int y = place->y();
    int d = distanceSeuil;
    float score = 0;
	Espece especeGroupe = groupe.espece();

    for (int i(x-d);i<x+d+1;i++){
        for (int j(y-d);j<y+d+1;j++){
            if (situation.dansPlateau(i,j)){
                if (situation.get(i,j)->occupant()== especeGroupe){
                    int distance = tMaximum(vabs(i-x),vabs(j-y));
                    score += situation.get(i,j)->nbOccupants()
						/pow(distance, exposant);
                }
            }
        }
    }

    return score;
}

float scoreCase(Situation& situation, Groupe& groupe, Case* place){

    /*Ici on va considérer trois scores qui dépendent du nombre d'unités autour de la cases
      (espece,ennemi,humain)
      On les compare avant de retourner le score final

      Par exemple, si scoreEnnemi>scoreHumain et distance

    */

    // D'abord on s'occupe des effets de bords, cad quand la case est mittoyenne et occupée par
    // des humains ou des ennemis



    //les paramètres

    float paramEnnemi    = -2;
    float exposantEnnemi = 2;

    float paramHumain    = 2;
    float exposantHumain = 2;

    float paramAmi       = 0;
    float exposantAmi    = 2;

    float paramVulnerabilite = 10;


    float param1 = 1;
    float param2 = 1;
    float param3 = 1;

    int distanceMax = place->distance(groupe.position());

    //Ici on attribue les scores que l'on va comparer
    //On peut modifier les arguments (exposant et distanceSeuil) pour améliorer l'heuristique

    float ennemiSco = scoreCaseEnnemi(situation, groupe, place,exposantEnnemi,distanceMax -1);
    float amiSco    = scoreCaseAmi(situation, groupe, place,exposantAmi,distanceMax);
    float humainSco = scoreCaseHumain(situation, groupe, place,exposantHumain,distanceMax);

    /* Ensuite on compare les score :
      le score correspond à la force d'une espèce dans une zone centrée sur une case
      - si le score ennemi est supérieur au score humain
            --> on peut alors supposer que l'ennemi va convertir les humains
            --> donc on augmente le score ennemi (en fonction du score humain)

      - si le score ami(de l'espèce) est supérieur au score humain
            --> de la même façon que précedemment, on augmente le score ami
            --> mais il faut vérifier que l'ennemi n'a pas un trop gros score dans cette zone

      - si le score ennemi est inférieur au score amiSco
            --> on suppose que l'on peut manger les ennemis
            --> on augmente le score ami

    */
    if (humainSco <= ennemiSco){
            ennemiSco += param1 * humainSco;
    }

    if (humainSco <= amiSco){
        if (ennemiSco <= humainSco){
            amiSco += param2 * humainSco;
        }
    }
	else {
		humainSco = 0;
	}

    if (ennemiSco <= amiSco){
        amiSco += param3 * ennemiSco;

    }


    float score = 0;

    score += paramEnnemi * ennemiSco;
    score += paramHumain * humainSco;
    score += paramAmi    * amiSco;
    score += EstVulnerablePourGroupe(groupe, place)*paramVulnerabilite;

    // ici on multiplie/divise le score par le nombre d'unité du groupe
    // --> ne sert que si on envisage de séparer les groupes

    score /= pow(groupe.effectif(), 0.5);

    return score;

}



int EstVulnerablePourGroupe(Groupe& groupe, Case *place){
    /* renvoie un entier dans {-1, 0 , 1}

      En cas de combat :
       - renvoie  1  si le groupe est gagnant
       - renvoie -1  si le groupe est perdant
       - renvoie  0 si la case est vide ou occupé par la même espèce

    */

    if (HUMAIN==place->occupant()){
        if (place->nbOccupants() <= groupe.effectif())
            return 1;

        else
            return -1;
    }

    if (place->occupant()==groupe.especeEnnemie()){
        if (1.5 * place->nbOccupants() <= groupe.effectif())
            return 1;

        else
            return -1;
    }

    else
        return 0;
}

int estAvantageuse(Groupe* groupe, Case* place){
	return 1;
}

//int nbDeDivisionAEnvisager(Groupe* groupe){
//    /*
//      cette fonction retourne le nombre division à envisager pour un groupe
//      en fontion du plateau :
//      - (son effectif)
//      - la proximité de maisons
//      - la proximité d'ennemis
//
//      */
//    float paramDiv = 5;
//
//    //int effectif          = groupe->effectif();
//    float proximiteMaison = scoreCaseHumain(groupe,groupe->position(),1,4);
//    float proximiteEnnemi = scoreCaseEnnemi(groupe,groupe->position(),1,4);
//
//    float resultat = (proximiteMaison + proximiteEnnemi) / paramDiv ;
//
//    return resultat;
//
//}

