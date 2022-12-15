#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "election.h"

void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod8, *mod9, *mod10, *mod11, *mod12, *mod13, *mod14, *pInfo;
election p;
int a=0;
int id;
char conseillers[20];
FILE *f;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod8=lookup_widget(objet,"mod8");
mod9=lookup_widget(objet,"mod9");
mod10=lookup_widget(objet,"mod10");
mod11=lookup_widget(objet,"mod11");
mod12=lookup_widget(objet,"mod12");
mod13=lookup_widget(objet,"mod13");
mod14=lookup_widget(objet,"mod14");
id = atoi(gtk_entry_get_text(GTK_ENTRY(mod4)));
f = fopen("election.txt","r");
if(f!=NULL){
while(fscanf(f,"%d %d %s %d %d %d %d\n",&(p.id),&(p.habitants),p.municipalite,&(p.conseillers),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
		if(id==p.id){
			a=1;
			break;
                 }
	}
fclose(f);
}
if(a==1){
sprintf(conseillers,"%d",p.conseillers);
gtk_entry_set_text(GTK_ENTRY(mod3),p.municipalite);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod1),p.d.j);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod2),p.d.m);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod3),p.d.a);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod5),p.habitants==0?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod6),p.habitants==1?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod7),p.habitants==2?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod8),p.habitants==3?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod9),p.habitants==4?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod10),p.habitants==5?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod11),p.habitants==6?TRUE:FALSE);
gtk_entry_set_text(GTK_ENTRY(mod12),p.municipalite);
gtk_entry_set_text(GTK_ENTRY(mod13),conseillers);
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Election introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod8, *mod9, *mod10, *mod11, *mod12, *mod13, *mod14, *pInfo;
election u;
char* ch = (char *) malloc(500);
strcpy(ch,"");
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod8=lookup_widget(objet,"mod8");
mod9=lookup_widget(objet,"mod9");
mod10=lookup_widget(objet,"mod10");
mod11=lookup_widget(objet,"mod11");
mod12=lookup_widget(objet,"mod12");
mod13=lookup_widget(objet,"mod13");
mod14=lookup_widget(objet,"mod14");
bool a=gtk_toggle_button_get_active(GTK_CHECK_BUTTON(mod14));
if(strcmp(gtk_entry_get_text(GTK_ENTRY(mod12)),"")==0)
strcat(ch,"Veuillez écrire la municipalité\n");
if(strcmp(gtk_entry_get_text(GTK_ENTRY(mod13)),"")==0)
strcat(ch,"Veuillez écrire le nombre de conseillers\n");
if(!a)
strcat(ch,"Veuillez confirmer");
if(strcmp(ch,"")==0){
u.id=atoi(gtk_entry_get_text(GTK_ENTRY(mod4)));
strcpy(u.municipalite,gtk_entry_get_text(GTK_ENTRY(mod12)));
u.d.j=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod1));
u.d.m=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod2));
u.d.a=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod3));
u.habitants=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod5))?0:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod6))?1:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod7))?2:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod8))?3:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod9))?4:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod10))?5:6;
u.conseillers=atoi(gtk_entry_get_text(GTK_ENTRY(mod13)));
modifier(u,"election.txt");
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	guint id;
	GtkWidget *pInfo, *objet, *af;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path)){
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer cette élection?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer(id,"election.txt");
	afficher(treeview,"election.txt","","","");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}
}


void
on_button_af_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af;
af=create_af();
gtk_widget_show(af);
treeview=lookup_widget(af,"treeview");
afficher(treeview,"election.txt", "","","");
}


void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj1, *aj2, *aj3, *aj4, *aj5, *aj6, *aj7, *aj8, *aj9, *aj10, *aj11, *aj12, *aj13, *aj14, *pInfo;
election u;
char *ch = (char *) malloc(500);
strcpy(ch,"");
aj1=lookup_widget(objet,"aj1");
aj2=lookup_widget(objet,"aj2");
aj3=lookup_widget(objet,"aj3");
aj4=lookup_widget(objet,"aj4");
aj5=lookup_widget(objet,"aj5");
aj6=lookup_widget(objet,"aj6");
aj7=lookup_widget(objet,"aj7");
aj8=lookup_widget(objet,"aj8");
aj9=lookup_widget(objet,"aj9");
aj10=lookup_widget(objet,"aj10");
aj11=lookup_widget(objet,"aj11");
aj12=lookup_widget(objet,"a12");
aj13=lookup_widget(objet,"aj13");
aj14=lookup_widget(objet,"aj14");
bool a=gtk_toggle_button_get_active(GTK_CHECK_BUTTON(aj14));
if(strcmp(gtk_entry_get_text(GTK_ENTRY(aj4)),"")==0)
strcat(ch,"Veuillez écrire l'id\n");
if(strcmp(gtk_entry_get_text(GTK_ENTRY(aj12)),"")==0)
strcat(ch,"Veuillez écrire la municipalité\n");
if(strcmp(gtk_entry_get_text(GTK_ENTRY(aj13)),"")==0)
strcat(ch,"Veuillez écrire le nombre de conseillers\n");
if(!a)
strcat(ch,"Veuillez confirmer");
if(strcmp(ch,"")==0){
u.id=atoi(gtk_entry_get_text(GTK_ENTRY(aj4)));
strcpy(u.municipalite,gtk_entry_get_text(GTK_ENTRY(aj12)));
u.d.j=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj1));
u.d.m=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj2));
u.d.a=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj3));
u.habitants=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj5))?0:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj6))?1:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj7))?2:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj8))?3:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj9))?4:gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj10))?5:6;
u.conseillers=atoi(gtk_entry_get_text(GTK_ENTRY(aj13)));
ajouter(u,"election.txt");
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_button5_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj;
aj=lookup_widget(objet,"aj");
aj=create_aj();
gtk_widget_show(aj);
}


void
on_button6_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj;
aj=lookup_widget(objet,"mod");
aj=create_mod();
gtk_widget_show(aj);
}


void
on_button7_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af, *e1, *e2, *e3;
char date[20], municipalite[20], id[10];
af=lookup_widget(objet,"af");
treeview=lookup_widget(af,"treeview");
e1=lookup_widget(objet, "entry1");
e2=lookup_widget(objet, "entry2");
e3=lookup_widget(objet, "entry3");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(e1)));
strcpy(municipalite,gtk_entry_get_text(GTK_ENTRY(e2)));
strcpy(date,gtk_entry_get_text(GTK_ENTRY(e3)));
afficher(treeview, "election.txt", id, municipalite, date);
}


void
on_button8_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *pInfo;
char ch[100];
float x = TPE("user.txt");
sprintf(ch, "Taux de participation : %.2f", x);
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}


void
on_button15_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *pInfo;
char *ch = TPHF("user.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}


void
on_button16_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj , * af ;
	
	aj = lookup_widget(objet,"aj");
	gtk_widget_destroy(aj);
	af=create_af();
	gtk_widget_show(af);
}


void
on_button17_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod , * af ;
	
	mod = lookup_widget(objet,"mod");
	gtk_widget_destroy(mod);
	af=create_af();
	gtk_widget_show(af);
}

