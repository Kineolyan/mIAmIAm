// mIAmIAm.cpp�d�finit le point d'entr�e pour l'application

#include "IA/joueurIA.h"
#include "util/timer.h"
#include "arbre/gestionnaireNoeuds.h"

const float FLOAT_MIN = -100000;
const float FLOAT_MAX = 100000;
const double DOUBLE_MIN = -100000;
const double DOUBLE_MAX = 100000;

using namespace std;

int main(int argc, char* argv[]) {
	if (argc<3) {
		cerr << "Configurer l'execution avec <host> <port>" << endl;
		return -1;
	}
	try {
		// Creation des singletons
		Create<Timer>();
		Create<GestionnaireNoeuds>();
		Get<GestionnaireNoeuds>().init(300);

		// Paramètres par défaut
		string nom = "mIAm";

		int nbOption = argc - 3;
		if (0!=nbOption%2) {
			cerr << "Une des options n'a pas de valeur, ou valeur sans option" << endl;
			return 0;
		}
		int i = 1;
		while (i<=nbOption) {
			string option = argv[i++],
					valeur = argv[i++];
			if ("--nom"==option || "-n"==option) {
				nom = valeur;
			}
		}

		JoueurIA* nous = new JoueurIA(nom, argv[argc - 2], argv[argc - 1]);
		nous->preparerPartie();
		nous->jouer();

		delete nous;
	}
	catch(const exception& e) {
		cerr << e.what() << endl;
	}

	Destroy<Timer>();
	Destroy<GestionnaireNoeuds>();
	return 1;
}

