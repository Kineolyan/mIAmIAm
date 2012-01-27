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
		JoueurPhysique* nous = new JoueurPhysique("mIAmPhy", argv[1], argv[2]);
		nous->preparerPartie();
		nous->jouer();

		return 0;
	}
	catch(const exception& e) {
		cerr << e.what() << endl;
	}
}

