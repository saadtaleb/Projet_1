#ifndef FONCTIONS_H_
#define FONCTIONS_H_
}
typedef struct agents 
{char prenom[30];
char nom [30]; 
double cin;
}agents;
typedef struct bureau_vote { 
int numer_bureau; 
char etat[100]; 
char municipalite[100] ;
char adress[100]; 
int capacite_e; 
int capacite_o;
agents agent;
 
} 
bureau_vote; 
#endif 
