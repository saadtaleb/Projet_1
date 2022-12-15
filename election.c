#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "election.h"
#include "callbacks.h"
#include <gtk/gtk.h>

enum
{
	ID,
	HABITANTS,
	MUNICIPALITE,
	DATE,
	CONSEILLERS,
	COLUMNS
};


void ajouter(election u, char *fname){
GtkWidget *pQuestion;
FILE *f;
int b=0;
gpointer user_data;
election p;
f=fopen(fname,"a+");
if(f!=NULL)
{	
	while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{	
		if(u.id==p.id)
		b=1;
	}
	if(b==0){
	fprintf(f,"%d %d %s %d %d %d %d\n",u.id,u.habitants,u.municipalite,u.conseillers,u.d.j,u.d.m,u.d.a);
	}
	pQuestion=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,b==0?GTK_MESSAGE_INFO:GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,b==0?"Election ajoutée avec succès !":"Election déja existante !");
	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pQuestion);
	break;
	}
	fclose(f);
}
}

void modifier(election u, char *fname){
election p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
		if(p.id!=u.id)
			fprintf(g,"%d %d %s %d %d %d %d\n",p.id,p.habitants,p.municipalite,p.conseillers,p.d.j,p.d.m,p.d.a);
		else
			fprintf(g,"%d %d %s %d %d %d %d\n",p.id,u.habitants,u.municipalite,u.conseillers,u.d.j,u.d.m,u.d.a);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Election modifiée avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

void afficher(GtkWidget *liste, char *fname, char *id, char *municipalite, char *date)
{
election p;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar date_election[50], habitants[20];
FILE *f;

store=gtk_tree_view_get_model(liste);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" ID", renderer,"text",ID, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Habitants", renderer,"text",HABITANTS, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Municipalite", renderer,"text",MUNICIPALITE, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_resizable(column,TRUE);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Date", renderer,"text",DATE, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Conseillers", renderer,"text",CONSEILLERS, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);



store=gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
if (strcmp(id,"")==0&&strcmp(municipalite,"")==0&&strcmp(date,"")==0){
f=fopen(fname,"a+");
if(f!=NULL)
{
		while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
sprintf(date_election,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
sprintf(habitants,p.habitants==0?"-5000":p.habitants==1?"5001 - 10000":p.habitants==2?"10001 - 25000":p.habitants==3?"25001 - 50000":p.habitants==4?"50001 - 100000":p.habitants==5?"100001 - 500000":"500000+");
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ID,p.id,HABITANTS,habitants,MUNICIPALITE,p.municipalite,DATE,date_election,CONSEILLERS,p.conseillers,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
else{
f = fopen(fname,"a+");
if(f!=NULL){
		while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
sprintf(date_election,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
if(p.id==atoi(id)||strcmp(p.municipalite,municipalite)==0||strcmp(date_election,date)==0){
sprintf(habitants,p.habitants==0?"-5000":p.habitants==1?"5001 - 10000":p.habitants==2?"10001 - 25000":p.habitants==3?"25001 - 50000":p.habitants==4?"50001 - 100000":p.habitants==5?"100001 - 500000":"500000+");
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ID,p.id,HABITANTS,habitants,MUNICIPALITE,p.municipalite,DATE,date_election,CONSEILLERS,p.conseillers,-1);
}
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
gtk_tree_view_set_reorderable(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_search_column(GTK_TREE_VIEW(liste),0);
gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(liste),GTK_TREE_VIEW_GRID_LINES_BOTH);
}

void supprimer(int id, char *fname)
{
election p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f!=NULL&&g!=NULL){
	while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
		if(p.id!=id)
			fprintf(g,"%d %d %s %d %d %d %d\n",p.id,p.habitants,p.municipalite,p.conseillers,p.d.j,p.d.m,p.d.a);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Election supprimée avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

/*void chercher_bureau_multi(char * nums , char * adresse){
remove("bureau_recherche_mult.txt");
FILE*f=fopen("bureau.txt","r");
FILE*f1=fopen("bureau_recherche_mult.txt","a+");
bureau B;
while(fscanf(f,"%s %s %s %s %d %d\n",B.adresse,B.id_bureau,B.salle,B.id_agent,&B.cap_electeurs,&B.cap_observateur)!=EOF)
{
if( (strcmp(nums,B.salle)==0) && strcmp(adresse,B.adresse)==0 ){
fprintf(f1,"%s %s %s %s %d %d\n",B.adresse,B.id_bureau,B.salle,B.id_agent,B.cap_electeurs,B.cap_observateur);

}
}
fclose(f);
fclose(f1);
}*/




election chercher(int id, char *fname){
FILE *f;
election p, e={id:-1};
f=fopen(fname,"r");
if(f!=NULL)
{
	while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
	if(p.id==id)
            return p;
	}
	fclose(f);
}
    return e;

}

float TPE(char *filename){
FILE *f=fopen(filename,"r");
user u;
int nb_electeurs=0;
int nb_vote=0;
if(f!=0){ 
             
while(fscanf(f,"%s %s %d %d %s %d %d %d %d %s %d %d\n",u.nom,u.prenom,&(u.genre),&(u.role),u.nationalite,&(u.date.j),&(u.date.m),&(u.date.a),&(u.id),u.mdp,&(u.ncin),&(u.vote))!=EOF)
{
      if(u.role==1){
      nb_electeurs++;
      if(u.vote!=-1){
        nb_vote++;
 }
}
             }
fclose(f);
 }
return(((float)nb_vote/nb_electeurs)*100);
}

char* TPHF(char *filename){
FILE *f2=fopen(filename,"r");
user u;
int h=0, f=0, nb_vote=0;
if(f2!=NULL){ 
while(fscanf(f2,"%s %s %d %d %s %d %d %d %d %s %d %d\n",u.nom,u.prenom,&(u.genre),&(u.role),u.nationalite,&(u.date.j),&(u.date.m),&(u.date.a),&(u.id),u.mdp,&(u.ncin),&(u.vote))!=EOF)
   {
   if(u.role==1&&u.vote!=-1){
     nb_vote++;
   if(u.genre==0)
   h++;
   else
    f++;
  }
  }
fclose(f2);
}
float x = (float)h/nb_vote, y = (float)f/nb_vote;
char *ch = malloc(50);
sprintf(ch, "Hommes : %.2f\nFemmes : %.2f", x*100, y*100);
return ch; 
} 
