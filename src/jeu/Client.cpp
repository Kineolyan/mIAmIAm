#include "Client.h"

#include <boost/array.hpp>

using namespace std;
using boost::asio::ip::tcp;

Client::Client(const string& host, const string& port) :
	io_service(), socket(io_service)
{
	try{
		cout << "Creation du client vers "<< host << ":" << port << endl;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), host, port);
		tcp::resolver::iterator it = resolver.resolve(query);

		socket.connect(*it);

		cout << "Client connecte" << endl;
		connected = true;
	}
	catch (exception& e){
		cerr << "Echec de la connection: " << e.what() << endl;
		connected = false;
	}
}



Client::~Client() {
	cout << "deconnexion" << endl;
}


/* Envoi le nom du joueur au serveur.
 * Aucune verification sur la validite des coordonnees n'est effectuee.
 */
void Client::setNom(const string& nom) {
	size_t request_length = nom.size();
	char taille = (char)request_length;

	envoyer(string("NME")+taille+nom);
	cout << "--\nEnvoi du nom \"" << nom << "\"" << endl;
}




/* Envoi une commande de deplacement au serveur.
 * Aucune verification sur la validite des coordonnees n'est effectuee.
 */
void Client::deplacer(int xDepart, int yDepart, int xArrivee, int yArrivee, int nbrIndividus){
	cout << "--\nDeplacement de " << nbrIndividus << " unites "
		<< "de (" << xDepart << "," << yDepart << ") vers (" 
		<< xArrivee << "," << yArrivee << ")" <<endl;
	
	envoyer(string("MOV")+ (char)xDepart + (char)yDepart + (char)nbrIndividus + (char)xArrivee + (char)yArrivee);
}




/* Envoi une commande d'attaque au serveur.
 * Aucune verification sur la validite des coordonnees n'est effectuee.
 */
void Client::attaquer(int xCible, int yCible){
	
	char x = (char)xCible;
	char y = (char)yCible;
	
	envoyer(string("ATK")+x+y);
	cout << "--\nAttaque de la position (" << xCible << "," << yCible << ")" << endl;
}




/* Cette methode permet de traiter la derniere requete reeue.
 * Elle fonctionne : 
 * - en mode synchronise (si aucune requete n'est en attente, la methode attend la prochaine)
 * - sans timer (si aucune requete n'arrive, aucun mecanisme ne reprendra la main apres un certain temps)
 */
void Client::recevoir(){
	cout << "--\nReception des donnees... ";
	try{
		string codeAction = lireCommande();
		cout << "commande " << codeAction << " recue." << endl;

		if ("SET"==codeAction){
			//Definition de la taille de la grille.
			int hauteur = lireEntier();
			int largeur = lireEntier();
			cout << "La grille contient " << hauteur << " lignes et " << largeur << " colonnes." << endl;
		}else if("HUM"==codeAction){
			//Signale la position des humains
			int nbrMaisons = lireEntier();
			cout << "Il y a " << nbrMaisons << " maisons d'humains." << endl;
			for(int i=0; i < nbrMaisons; i++){
				int x = lireEntier();
				int y = lireEntier();
				cout << " - une maison en (" << x << "," << y << ")" << endl;
			}
		}else if("HME"==codeAction){
			//Indique les coordonnees de la case de depart
			int x = lireEntier();
			int y = lireEntier();
			cout << "Case depart : (" << x << "," << y << ")" << endl;
		}else if("UPD"==codeAction){
			//Mise e jour du plateau
			int nbrChangements = lireEntier();
			for(int i=0; i < nbrChangements; i++){
				int x = lireEntier();
				int y = lireEntier();
				int h = lireEntier();
				int v = lireEntier();
				int l = lireEntier();
				cout << " - la case (" << x << "," << y << ") contient desormais "
					<< h << " humains, "<< v << " vampires et " << l << " loups-garous." 
					<< endl;
			}
		}else if("END"==codeAction){
			cout << "Partie terminee";
		}else if("BYE"==codeAction){
			cout << "Connexion interrompue";
		}else{
			cout << "Commande non reconnue: " << codeAction << endl;
		}
	}
	catch(exception e){
		cerr << "Echec lors de la reception : " << e.what() << endl;
	}
}

/* Methodes privees */

void Client::envoyer(string msg){
	cout << "Envoi de la commande: \"" << msg << "\"" << endl;
	try{
		boost::asio::write(socket, boost::asio::buffer(msg), boost::asio::transfer_all());//Option transfert_all utile?
	}
	catch(exception e){
		cerr << "Echec de l'envoie de la commande : " << e.what() << endl;
	}
}

int Client::lireEntier(){
	char buf[1];
	socket.read_some(boost::asio::buffer(buf,1));
	int entier = (int)buf[0];
	return entier;
}

string Client::lireCommande(){
	char buf[3];
	socket.read_some(boost::asio::buffer(buf, 3));
	string chaine(buf);
	return chaine.substr(0,3);
}




