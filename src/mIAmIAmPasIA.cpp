// mIAmIAm.cpp�d�finit le point d'entr�e pour l'application

#include "jeu/joueurPhysique.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc<3) {
		cout << "Configurer l'execution avec <host> <port>" << endl;
		return -1;
	}
	try {
		// Paramètres par défaut
		string nom = "mIAmPhy";

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

		JoueurPhysique* nous = new JoueurPhysique(nom, argv[argc - 2], argv[argc -1]);
		nous->preparerPartie();
		nous->jouer();

		delete nous;
		return 0;
	}
	catch(const exception& e) {
		cerr << e.what() << endl;
	}
}

