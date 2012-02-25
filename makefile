#Zatacka Makefile
#Copyright by Mage 2006

SRC = ./src
OBJ = ./obj
BIN = ./bin

CC = g++ 
DEFS =  
INCLUDES =  -I $(SRC)/ \
	-I /home/oliv/workspaces/bibliothèques/boost_1_48_0/ \
	-I /usr/local/include/
LIBS = -lboost_system -lboost_thread -lpthread
OPTIONS = 
OS = unix
DEFS += -DDEBUG_ACTIVE=1
OPTIONS += -ggdb
PROGNAME_IA = mIAmIAm
PROGNAME_J = mIAmIAmPasIA
PROGNAME_TEST = testIA

DEFINES = $(INCLUDES) $(LIBS) $(DEFS) $(OPTIONS)
CFLAGS = $(DEFINES) -Wall

OBJS_COMMUNS = $(OBJ)/Client.o \
	$(OBJ)/joueur.o

OBJS_IA = $(OBJS_COMMUNS) \
	$(OBJ)/plateau.o \
	$(OBJ)/groupe.o \
	$(OBJ)/IA.o \
	$(OBJ)/joueurIA.o \
	$(OBJ)/noeud.o \
	$(OBJ)/gestionnaireNoeuds.o \
	$(OBJ)/strategieSimple.o
	

OBJS_J = $(OBJS_COMMUNS) \
	$(OBJ)/joueurPhysique.o
	

OBJS_TEST = $(OBJS_IA)

$(OBJ)/%.o: $(SRC)/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/jeu/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/jeu/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/util/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/util/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/IA/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/IA/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/arbre/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/arbre/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

# Dépendances

# Sur le dossier jeu
$(OBJ)/Client.o: $(SRC)/jeu/Client.cpp \
	$(SRC)/jeu/Client.h
$(OBJ)/joueur.o: $(SRC)/jeu/joueur.cpp \
	$(SRC)/jeu/joueur.h \
	$(SRC)/jeu/plateau.h
$(OBJ)/joueurPhysique.o: $(SRC)/jeu/joueurPhysique.cpp \
	$(SRC)/jeu/joueurPhysique.h \
	$(SRC)/jeu/joueur.h
$(OBJ)/plateau.o: $(SRC)/jeu/plateau.cpp \
	$(SRC)/jeu/plateau.h

# Sur le dossier src
$(OBJ)/mIAmIAm.o: $(SRC)/mIAmIAm.cpp \
	$(SRC)/IA/joueurIA.h
$(OBJ)/mIAmIAmPasIA.o: $(SRC)/mIAmIAmPasIA.cpp \
	$(SRC)/jeu/joueurPhysique.h

# Commandes executables

all: IA joueur
	
IA: $(OBJS_IA) $(OBJ)/mIAmIAm.o
	@$(CC) $(CFLAGS) -o $(PROGNAME_IA) $^ $(LIBS)
	@mv $(PROGNAME_IA) $(BIN)
	@echo -- program created as: $(PROGNAME_IA) --
	
joueur: $(OBJS_J) $(OBJ)/mIAmIAmPasIA.o
	@$(CC) $(CFLAGS) -o $(PROGNAME_J) $^ $(LIBS)
	@mv $(PROGNAME_J) $(BIN)
	@echo -- program created as: $(PROGNAME_J) --
	
test: $(OBJS_TEST) $(OBJ)/test.o
	@$(CC) $(CFLAGS) -o $(PROGNAME_TEST) $^ $(LIBS)
	@mv $(PROGNAME_TEST) $(BIN)
	@echo -- program created as: $(PROGNAME_TEST) --


prepare:
	@if test ! -d $(OBJ); then mkdir $(OBJ); echo -- obj/ created --; fi
	 
clean:	
	@rm -f $(OBJ)/*.o
	@rm -f $(BIN)/$(PROGNAME_IA)
	@rm -f $(BIN)/$(PROGNAME_J)
	@echo -- .o and program erased --

install: prepare all

reset: clean all

