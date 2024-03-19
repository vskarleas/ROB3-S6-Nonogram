#############################################################################
# Fichier Makefile 
# UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
# Author: Vasileios Filippos Skarleas - All rights reserved.
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################

# Chaque exercise ies identifie par un programme principale nomé comme exercise_xxx.c 
# Les programmes peuvent etre base sur d'autres fonctionctions definies aux different fichiers

#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = main complet partial t_tests automatic

#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

utile.o:  utile.c utile.h constants.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

algos.o : algos.c algos.h constants.h api.h memory.h tables.h ui.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

api.o : api.c api.h algos.h constants.h memory.h tables.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

bitmap.o : bitmap.c bitmap.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

decode.o : decode.c decode.h utile.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

memory.o : memory.c memory.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tables.o : tables.c tables.h constants.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

ui.o : ui.c ui.h constants.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

main.o : main.c utile.h algos.h constants.h decode.h memory.h tables.h ui.h bitmap.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

automatic.o : automatic.c utile.h algos.h constants.h decode.h memory.h tables.h ui.h bitmap.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

complet.o : complet.c utile.h algos.h constants.h decode.h memory.h tables.h ui.h bitmap.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

partial.o : partial.c utile.h algos.h constants.h decode.h memory.h tables.h ui.h bitmap.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

t_tests.o : t_tests.c utile.h algos.h constants.h decode.h memory.h tables.h ui.h bitmap.h
	@echo ""
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
########################################################
# regles explicites de creation des executables

main : main.o utile.o ui.o tables.o memory.o decode.o bitmap.o api.o algos.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

complet : complet.o utile.o ui.o tables.o memory.o decode.o bitmap.o api.o algos.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

partial : partial.o utile.o ui.o tables.o memory.o decode.o bitmap.o api.o algos.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

t_tests : t_tests.o utile.o ui.o tables.o memory.o decode.o api.o algos.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

automatic : automatic.o utile.o ui.o tables.o memory.o decode.o bitmap.o api.o algos.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
