// mIAmIAm.cpp�d�finit le point d'entr�e pour l'application

#include "IA/joueurIA.h"
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc<4) {
		cerr << "Configurer l'execution avec <host> <port> <espece>" << endl;
		return -1;
	}
	try {
		Espece especeJoueur;
		if (0==strcmp(argv[3], "vampire")) {
			especeJoueur = VAMPIRE;
		}
		else if (0==strcmp(argv[3], "loup")) {
			especeJoueur = LOUP;
		}
		else {
			cerr << "Espece incorrecte. Choix possibles: 'vampire', 'loup'." << endl;
			return -1;
		}

		JoueurIA* nous = new JoueurIA("mIAm", argv[1], argv[2], especeJoueur);
		nous->preparerPartie();
		nous->jouer();

		delete nous;
		return 0;
	}
	catch(const exception& e) {
		cerr << e.what() << endl;
	}
}

