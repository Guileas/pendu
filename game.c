#include <stdio.h>
#include <stdlib.h>
//pour le rand
#include <time.h>
//gere les chaine de caractere
#include <string.h>
//Gere nos prototypes
#include "game.h"
//Pour transformer les min en max
#include <ctype.h>

#define TAILLE_MAX 100

//Pour dessiner le bonhomme
void dessin(int nbrCoup)
{
    //En fonction du nombre de coup restant
}

//Pour choisir un chiffre
int randNumber(int maximum)
{
    const int MIN = 1;
    srand(time(NULL));
    int max = (rand() % (maximum - MIN +1))+ MIN;
    return max;
}

//Pour gérer le dico on renvoie un pointeur sur une chaine de caractere
char* dico()
{
    FILE *fichier = NULL;
    int i = 0,  j = 0, entier = 0;
    //On crée un pointeur et on lui assigne une place en mémoire
    //pour pouvoir le passer à une autre fonction
    char* chaine = malloc(TAILLE_MAX * sizeof(char));

    fichier = fopen("pendu.txt", "r");

    //Vérifie que le fichier a bien été ouvert
    if(fichier != NULL)
    {
        //Récupère le nombre de mot dans le fichier
        while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
            i = i + 1;
        }
        //Reviens au début du fichier
        rewind(fichier);
        //Récupération du mot
        while(j != randNumber(i))
        {
            fgets(chaine, TAILLE_MAX, fichier);
            j = j + 1;
        }

        //printf("%s", chaine);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier");
    }

    return chaine;
}

void menu()
{
    system("cls");
    char choix = 0;
    printf("\t\tPendu\n\n");
    printf("\t1 - Regles du jeu\n");
    printf("\t2 - Partie Solo\n");
    printf("\t3 - 1 VS 1\n");
    printf("\t4 - Quitter\n\n");

    printf("\tVotre choix? ");
    scanf("%d", &choix);
    modeDeJeux(choix);
}

//Affichage des regles
void regles()
{
    int choix = 0;
    system("cls");
    printf("\t\tRegles\n");
    printf("\tLe but est simple, trouver le mot mystere.\n");
    printf("\tPour cela vous avez 10 chance\n");
    printf("\tLorsque vous entrez un lettre le resultat peux prendre 2 formes differentes\n");
    printf("\tSoit votre lettre ce situe dans le mot, dans ce cas chaque occurence de la lettre seront revele\n");
    printf("\tSoit votre lettre ne se trouve pas dans le mot et vous perdez une chance\n");
    printf("\tLes mots ne contiennent ni espace ni ponctuation\n");
    printf("\tSi au bout de vos 10 essais vous n'avez pas trouver le mot vous etes definitivement pendus\n");
    printf("\tBonne chance a vous!\n\n");

    printf("\t1.Retourner au menu, 2.Arreter le jeux ");
    scanf("%d", &choix);

    switch(choix)
    {
    case 1:
        menu();
        break;
    case 2:
        return 0;
        break;
    }
}

void modeDeJeux(int choix)
{
    switch(choix)
    {
    case 1:
        regles();
        break;
    case 2:
        solo();
        break;
    case 3:
        multi();
        break;
    case 4:
        return 0;
        break;
    }
}


void replay()
{
    int choix;
    printf("\n");
    printf("\tVoulez vous rejouer? \n");
    printf("\t1 - Retour au menu\n");
    printf("\t2 - Quitter le jeu\n");
    printf("\t");
    scanf("%d", &choix);
    fflush(stdin);

    switch(choix)
    {
    case 1:
        menu();
        break;
    case 2:
        return 0;
        break;
    }

}

//Gestion de la partie ne mode solo
void solo()
{
    system("cls");
    int coup = 10;
    int j = 0;
    char *mot = dico();
    int tailleMot = strlen(mot);
    int *verif = NULL, i =0;
    verif = malloc(tailleMot * sizeof(int));
    char entree = "";

    //Initialisation de vérif
    if(verif == NULL)
    {
        exit(0);
    }
    for(i=0; mot[i] != '\n'; i++)
    {
        verif[i] = 0;
    }
    int testEntree =  strcmp(mot, verif);
    printf("\t\tMode Solo\n\n");
    motAffichage(mot);
    //Répétition de la demande d'entrée tant que le mot n'a pas été trouvé
    while(!gagne(mot, verif) && coup > 0)
    {
        printf("\tChoisissez une lettre : ");
        entree = viderBufer();
        verification(entree, mot, &coup, verif);
    }

    //Vérifi si les 2 tableaux sont identiques
    if(gagne(mot, verif))
    {
        printf("\n\tBravo vous avez gagner!\n\n");
    }
    else
    {
        printf("\n\tVous avez perdus!\n\n");
    }

    replay();
}

//Verifie que toutes les lettres ont été trouvé
int gagne(char* mot, int* verif)
{
    int i = 0;
    int gagne = 1;

    for(i=0; i < strlen(mot); i++)
    {
        if(verif[i] == 0)
        {
            gagne = 0;
        }
    }

    return gagne;
}

//Gestion de l'entrée utilisateur
//Vide le cache ou "buffer" pour éviter le depassement de mémoire ou l'arret du programme à cause du \n de fin de scanf
char viderBufer()
{
    char caracter = 0;
    caracter = getchar();
    caracter = toupper(caracter);
    while(getchar() != '\n');

    return caracter;
}


void motAffichage(const char* mot)
{
    int i = 0;
    int tailleChaine = strlen(mot);
    printf("\tMot a trouve : ");
    for(i=0; i<tailleChaine; i++)
    {
        printf(" _ ");
    }
    printf("\n");
}

void verification(char lettre, char* mot, int *coup, int* verif)
{
    int i;
    char *resultat = NULL;
    printf("\t");
    //Cherche la lettre dans le mot
    resultat = strchr(mot, lettre);
    //Affiche les lettres après vérification
    for(i=0; mot[i] != '\n'; i++)
    {
        if(mot[i] == lettre)
        {
            verif[i] = 1;
            printf(" %c ", mot[i]);
        }
        else
        {
            if(verif[i] == 1)
            {
                printf(" %c ", mot[i]);
            }
            else
            {
                printf(" * ");
            }
        }
    }

    //Gere les coups
    if(resultat != NULL)
    {
        printf("\n\n\tVous avez encore %d chance \n\n", *coup);
    }
    else
    {
        *coup = *coup - 1;
        printf("\n\n\tIl ne vous reste que %d chance \n\n", *coup);
    }
}

//Mode multijoueur
void multi()
{
    system("cls");
    int i = 0, j1 = 1, j2 = 0, coup1 = 10, coup2 = 10;
    printf("\t1 VS 1\n");
    char *mot = dico();
    char lettre;
    int *verif = NULL;
    verif = malloc(strlen(mot) * sizeof(int));

    //Initialisation de vérif
    if(verif == NULL)
    {
        exit(0);
    }
    for(i=0; mot[i] != '\n'; i++)
    {
        verif[i] = 0;
    }
    printf("\n");
    motAffichage(mot);


    while(coup1 >0 && coup2>0 && !gagne(mot,verif))
    {
        if(j1 == 1)
        {
            printf("\tJoueur 1, choisissez une lettre : ");
            lettre = viderBufer();
            verification(lettre, mot, &coup1, verif);
            j1 = 0;
            j2 = 1;
        }
        else
        {
            printf("\tJoueur 2, choisissez une lettre : ");
            lettre = viderBufer();
            verification(lettre, mot, &coup2, verif);
            j1 = 1;
            j2 = 0;
        }
    }

    if(gagne(mot,verif))
    {
        if(coup1 < coup2)
        {
            printf("\tLe joueur 1 à gagne !!\n");
        }
        else
        {
            printf("\tLe joueur 2 a gagne !!\n");
        }

    }else
    {
        if(coup1 == 0)
        {

            printf("\tLe joueur 1 a perdus\n");
        }else if(coup2 == 0)
        {
            printf("\tLe joueur 2 a perdus\n");
        }
    }

    replay();
}
