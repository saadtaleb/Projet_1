#ifndef FONCTIONS_H_
#define FONCTIONS_H_
}

typedef struct bureau_vote { 
int numero_bureau; 
int salle;
char adress[100];
int capacite_e; 
int capacite_o; 
int id_agent;
} 
bureau_vote; 
int ajouter(char *, bureau_vote );
int modifier( char *, int, bureau_vote );
int supprimer(char *, int );
point chercher(char *, int);

#endif 
