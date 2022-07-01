#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include "head.h"
 

//la fonction qui cree la liste des gueris
gueri* creerListG(gueri *debut)
{
	donnees *d;
	gueri *g;
	FILE *f;
	int age,i;
	char *ville,*nom,*jour,*cin;
	
    f=fopen("Fichier_Gueris2.txt","r");
    if(f!=NULL)
     { 
        while(!feof(f))
     	  {
     	  	d=(donnees*)malloc(sizeof(donnees));
            g=(gueri*)malloc(sizeof(gueri));
            nom=(char*)malloc(sizeof(char));
	        ville=(char*)malloc(sizeof(char));
	        cin=(char*)malloc(sizeof(char));
	        jour=(char*)malloc(sizeof(char));
     	  	fscanf(f,"%s %s %s %s %d",nom,ville,cin,jour,&age);
     	  	d=CreerDonnees(cin,nom,ville,age);
     	  	g->info=d;
     	  	g->jour=jour;
     	  	g->suivant=debut;
     	  	debut=g;	
	      } 
		debut=debut->suivant; 	
	 }
   return debut; 
}

//la fonction qui va ajouter un gueri
gueri* AjouterGueri(char *cin,char *nomc,char *ville,int age,char *jour,gueri *debut, patient *tete)
{ 
    int i=-1;
    patient *p=tete;
                         //j'ai utilise la structure patient pour rechercher le nouveau gueri dans la liste des patients 
   gueri *g;           //si le nouveau gueri existe dans la liste des patients donc il faut le supprimer de cette liste
   donnees *d=(donnees*)malloc(sizeof(donnees));
   g=(gueri*)malloc(sizeof(gueri));
   
   d=CreerDonnees(cin,nomc,ville,age);
   g->info=d;   
   g->jour=jour;
   if(debut==NULL)
     {
     	debut=g;
     	g->suivant=NULL;
	 }
	else
	  {
	    g->suivant=debut;
		debut=g;	
	  } 
	while(p!=NULL && strcmp(p->info->cin,cin)!=0) 
	    p=p->suivant; 
    if(p!=NULL)
     {
	   tete=supprimerPatient(tete,cin); 
	   ecrireFichier(tete);
	  }  
     
    return debut;
}

//la fonction qui ecrit la liste des gueris dans le fichier des gueris
void ecrireFichierG(gueri *debut)
{
	gueri *g;
	FILE *f;
	f=fopen("Fichier_Gueris2.txt","w");
	if(f!=NULL)
	 {
	 	g=debut;
	 	while(g!=NULL)
	 	 {
		   fprintf(f,"%s %s %s %s %d\n",g->info->nomc,g->info->ville,g->info->cin,g->jour,g->info->age);
		   g=g->suivant;   		
		  }
		fclose(f);
	 }
}


//la fonction qui affiche la liste des gueris
void AffichageG(gueri *debut)
{
	gueri *tmp=debut;    //tmp :pointeur temporaire
    while (tmp!=NULL)
      {
        printf("[");
        printf("CIN: %s",tmp->info->cin);
        printf(" | Nom: %s",tmp->info->nomc);
        printf(" | Ville: %s",tmp->info->ville);
        printf(" | JOUR: %s",tmp->jour);
        printf(" | Age: %d",tmp->info->age);
        tmp=tmp->suivant;
        printf(" ]\n");
      }

    printf("\n\n\n");
}
	
//la fonction qui modifie les informations d'un gueri
gueri* modifierG(gueri *debut,char *nom,char *ville,int age,char *jour,char *cin)
{
	gueri *g;
	g=debut;
	while(g!=NULL&&strcmp(g->info->cin,cin)!=0)
	  g=g->suivant;
	if(g==NULL)
       printf("pas de gueri ayant ce cin %s",cin);
    else
    {
    	g->info->age=age;
    	g->info->ville=ville;
    	g->info->nomc=nom;
		g->jour=jour;	
	}
  return debut;	
}	

//la fonction qui supprime un gueri
gueri* supprimerGueri(gueri *debut,char *cin)
     {
       	gueri *g,*q;

       	g=debut;
       	if(g==NULL)
       	   	printf("la liste est vide, on peut rien supprimer \n");
       	else
		   {
		     	while(g!=NULL && strcmp(g->info->cin,cin)!=0)
		   	     {
		   	   	    q=g;
		   	        g=g->suivant;
			     } 
		   }
  	    if(g==NULL)
  	      {
  	      	printf("il n'y a pas de gueri ayant ce cin %s \n",cin);
		  }
	    else
		  {
		  	if(g==debut)            //c'est a dire que l'element a supprimer est le premier de la liste 
		  	  	debut=g->suivant;
		    else	        
			  q->suivant=g->suivant;
			
			 free(g);  	
		  }
		return debut;  		
	 }

//la fonction qui va lister les gueris selon la ville
int listerG_selon_ville(gueri *debut,char *nom_v)
{
	gueri *g;
	int i=0;       //cette fonction retourne un int juste pour traiter le cas ou on n'a pas de gueri dans la ville donnee
	g=debut;       //autrement dit dans le main o va faire le test sur la valeur retournee par la fonction
	              //si la valeur reste nulle c'est a dire qu'on a pas entre dans la boucle, du coup on n'a pas de gueri dans cette ville donnee.
	while(g!=NULL)
	 {
	 	if(strcmp(g->info->ville,nom_v)==0)
		 {
		   printf("[ ");
           printf("CIN: %s",g->info->cin);
           printf(" | Nom: %s",g->info->nomc);
           printf(" | Ville: %s",g->info->ville);
           printf(" | JOUR: %s",g->jour);
           printf(" | Age: %d",g->info->age);
           printf(" ]\n");
		   i=1;	
		 }
	   g=g->suivant;	
	 }
	 return i; 
}

//la fonction qui liste le nombre des gueris par ville
void nbr_Gueri_ville(Ville *debut,gueri *tete)
{
	gueri *g;
	Ville *v;
	v=debut;
	int cpt;
	while(v!=NULL)
	 {  
	    cpt=0;
	 	g=tete;
	    while(g!=NULL)
	     {
	    	if(strcmp(g->info->ville,v->nom_ville)==0)
	    	   	cpt++;
	    	g=g->suivant;   	
		 }
	    printf("le nombre des gueris de la ville %s est %d \n",v->nom_ville,cpt);	
		v=v->suivant;	
	 }	 
}

//la fonction qui retourne le taux de guerison par jour 
float taux_guerison(gueri *tete,patient *debut,char *jour)
{
	
 float nbr=0,cpt=0;
 while(tete!=NULL)
   {
   	    if(strcmp(tete->jour,jour)==0)
   	        cpt++;
    tete=tete->suivant; 	   
   }
  while(debut!=NULL)
   {
   	  nbr++;
	debut=debut->suivant;	   
   }
  cpt=(cpt/nbr);
  cpt=cpt*100;  
  return cpt; 		
}

//la fonction qui retourne le taux total des gueris
float taux_total_guerison(gueri *tete,patient *debut)
{
	
 float nbr=0,cpt=0;
 while(tete!=NULL)
   {
   	    cpt++;
        tete=tete->suivant; 	   
   }
  while(debut!=NULL)
   {
   	    nbr++;
	    debut=debut->suivant;	   
   }
  cpt=(cpt/nbr);
  cpt=cpt*100;  
  return cpt; 		
}
