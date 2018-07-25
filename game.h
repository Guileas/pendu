//Pour empêcher l'inclusion infini
#ifndef GAME.H
//On défini GAME.H
#define GAME.H

    #include <stdio.h>
    #include <stdlib.h>
    //pour le rand
    #include <time.h>
    //gere les chaine de caractere
    #include <string.h>
    //Gere nos prototypes

    void menu();
    int randNumber(int maximum);
    char* dico();
    void modeDeJeux(int choix);
    void regles();
    void solo();
    void motAffichage(const char* mot);
    void verification(char lettre, char* mot, int *coup, int* verif);
    void multi();
    char viderBufer();
    void replay();
    int gagne(char* mot, int* verif);

#endif
