#pragma once

#include <environnement.h>
#include <vector>
#include <boost/asio.hpp>


class Client
{
public:
	bool connected;
	
	Client(const std::string& host, const std::string& port);
	~Client();

	//commades d'envoi
	void setNom(const std::string& nom);
	void deplacer(int xDepart, int yDepart, int xArrivee, int yArrivee, int nbrIndividus);
	void attaquer(int xCible, int yCible);
	
	void recevoir();
	void envoyer(std::string msg);

	int lireEntier();
	std::string lireCommande();

private:
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket;
	
	
};

int mainClient(char* host, char* port);
