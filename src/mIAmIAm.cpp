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
		// Paramètres par défaut
		string nom = "mIAm";

		int nbOption = argc - 4;
		if (0!=nbOption%2) {
			cerr << "Une des options n'a pas de valeur, ou valeur sans option" << endl;
			return 0;
		}
		int i = 1;
		while (i<=nbOption) {
			string option = argv[i++],
					valeur = argv[i++];
			if ("-nom"==option) {
				nom = valeur;
			}
		}

		Espece especeJoueur;
		if (0==strcmp(argv[argc - 1], "vampire")) {
			especeJoueur = VAMPIRE;
		}
		else if (0==strcmp(argv[argc - 1], "loup")) {
			especeJoueur = LOUP;
		}
		else {
			cerr << "Espece incorrecte. Choix possibles: 'vampire', 'loup'." << endl;
			return -1;
		}

		JoueurIA* nous = new JoueurIA(nom, argv[argc - 3], argv[argc - 2], especeJoueur);
		nous->preparerPartie();
		nous->jouer();

		delete nous;
		return 0;
	}
	catch(const exception& e) {
		cerr << e.what() << endl;
	}
}

