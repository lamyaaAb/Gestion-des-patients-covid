#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include "head.h"


//la fonction qui cree la liste des deces a partir  du fichier
deces* creerListD(deces *debut)
{
	donnees *d;
	deces *D;
	FILE *f;
	int age,i;
	char *ville,*nom,*jour,*cin;
	
    f=fopen("Fichier_Deces2.txt","r");
    if(f!=NULL)
     { 
        while(!feof(f))
     	  {
     	  	d=(donnees*)malloc(sizeof(donnees));
            D=(deces*)malloc(sizeof(deces));
            nom=(char*)malloc(sizeof(char));
	        ville=(char*)malloc(sizeof(char));
	        cin=(char*)malloc(sizeof(char));
	        jour=(char*)malloc(sizeof(char));
     	  	fscanf(f,"%s %s %s %s %d",nom,ville,cin,jour,&age);
     	  	d=CreerDonnees(cin,nom,ville,age);
     	  	D->info=d;
     	  	D->jour=jour;
     	  	D->suivant=debut;
     	  	debut=D;	
	      } 
		debut=debut->suivant; 
	 }
   return debut; 
}

//la fonction qui va ajouter un decede
deces* AjouterDecede(char *cin,char *nomc,char *ville,int age,char *jour,deces *debut, patient *tete)
{ 
    int i=-1;
    patient *p=tete;
                         //j'ai utilise la structure patient pour rechercher le nouveau decede dans la liste des patients 
   deces *D;           //si le nouveau decede existe dans la liste des patients donc il faut le supprimer de cette liste
   donnees *d=(donnees*)malloc(sizeof(donnees));
   D=(deces*)malloc(sizeof(deces));
   
   d=CreerDonnees(cin,nomc,ville,age);
   D->info=d;   
   D->jour=jour;
   if(debut==NULL)
     {
     	debut=D;
     	D->suivant=NULL;
	 }
	else
	  {
	    D->suivant=debut;
		debut=D;	
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

//la fonction qui ecrit la liste des deces dans le fichier des deces
void ecrireFichierD(deces *debut)
{
	deces *D;
	FILE *f;
	f=fopen("Fichier_Deces2.txt","w");
	if(f!=NULL)
	 {
	 	D=debut;
	 	while(D!=NULL)
	 	 {
		   fprintf(f,"%s %s %s %s %d\n",D->info->nomc,D->info->ville,D->info->cin,D->jour,D->info->age);
		   D=D->suivant;   		
		  }
		fclose(f);
	 }
}


//la fonction qui affiche la liste des deces
void AffichageD(deces *debut)
{
	deces *tmp=debut;    //tmp :pointeur temporaire
    while (tmp!=NULL)
      {
        printf("[ ");
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

//la fonction qui supprime un decede
deces* supprimerDecede(deces *debut,char *cin)
     {
       	deces *D,*q;

       	D=debut;
       	if(D==NULL)
       	   	printf("la liste est vide, on peut rien supprimer ");
       	else
		   {
		     	while(D!=NULL && strcmp(D->info->cin,cin)!=0)
		   	     {
		   	   	    q=D;
		   	        D=D->suivant;
			     } 
		   }
  	    if(D==NULL)
  	      {
  	      	printf("il n'y a pas de decede ayant ce cin %s \n",cin);
		  }
	    else
		  {
		  	if(D==debut)            //c'est a dire que l'element a supprimer est le premier de la liste 
		  	  	debut=D->suivant;
		    else	        
			  q->suivant=D->suivant;
			
			 free(D);  	
		  }
		return debut;  		
	 }

//la fonction qui va lister les deces selon la ville
int listerD_selon_ville(deces *debut,char *nom_v)
{
	deces *D;
	int i=0;       //cette fonction retourne un int juste pour traiter le cas ou on n'a pas de deces dans la ville donnee
	D=debut;       //autrement dit dans le main o va faire le test sur la valeur retournee par la fonction
	              //si la valeur reste nulle c'est a dire qu'on a pas entre dans la boucle, du coup on n'a pas de deces dans cette ville donnee.
	while(D!=NULL)
	 {
	 	if(strcmp(D->info->ville,nom_v)==0)
		 {
		   printf("[");
           printf("CIN: %s",D->info->cin);
           printf(" | Nom: %s",D->info->nomc);
           printf(" | Ville: %s",D->info->ville);
           printf(" | JOUR: %s",D->jour);
           printf(" | Age: %d",D->info->age);
           printf(" ]\n");
		   i=1;	
		 }
	   D=D->suivant;	
	 }
	 return i; 
}

//la fonction qui liste le nombre des deces par ville
void nbr_Deces_ville(Ville *debut,deces *tete)
{
	deces *D;
	Ville *v;
	v=debut;
	int cpt;
	while(v!=NULL)
	 {  
	    cpt=0;
	 	D=tete;
	    while(D!=NULL)
	     {
	    	if(strcmp(D->info->ville,v->nom_ville)==0)
	    	   	cpt++;
	    	D=D->suivant;   	
		 }
	    printf("le nombre des deces de la ville %s est %d \n",v->nom_ville,cpt);	
		v=v->suivant;	
	 }	 
}

//la fonction qui retourne le taux de deces par jour 
float taux_deces(deces *tete,patient *debut,char *jour)
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

//la fonction qui retourne le taux de deces par jour et par ville 
float taux_deces_JV(deces *tete,patient *debut,char *jour,char *ville)
{	
 float nbr=0,cpt=0;
 while(tete!=NULL)
   {
   	    if(strcmp(tete->jour,jour)==0 && strcmp(tete->info->ville,ville)==0)
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

//la fonction qui retourne le taux total des deces  
float taux_total_deces(deces *tete,patient *debut)
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
