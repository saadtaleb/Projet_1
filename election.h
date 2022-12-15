#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gtk/gtk.h>
typedef struct Date
{
    int j;
    int m;
    int a;
}Date;

typedef struct{
char nom[50];
char prenom[50];
int genre;
int role;
char nationalite[50];
Date date;
int id;
char mdp[50];
int ncin;
int vote;
}user;

typedef struct election
{
int id;
int habitants;
char municipalite[50];
int conseillers;
Date d;
}election;



void ajouter(election u, char *fname);
void supprimer(int id, char *fname);
void modifier(election u, char *fname);
void afficher(GtkWidget *liste, char *fname, char *id, char *municipalite, char *date);
election chercher(int id, char *fname);
char* TPHF(char *filename);
float TPE(char *filename);

