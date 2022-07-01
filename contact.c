#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include "head.h"

/* ---------------------------------- Gestion des contacts des patients ---------------------------------- */

//creer la liste des contacts
contact* creerListC(contact *debut){
	donnees *d;
	contact *p;
	FILE *f;
	int age,i;
	char *ville,*nom,*cin,*etat,*cin_patient;
    f=fopen("Fichier_Contacts.txt","r");
    if(f!=NULL)
     { 
        while(!feof(f))
     	  {
     	  	d=(donnees*)malloc(sizeof(donnees));
            p=(contact*)malloc(sizeof(contact));
            nom=(char*)malloc(sizeof(char));
	        ville=(char*)malloc(sizeof(char));
	        cin=(char*)malloc(sizeof(char));
	        etat=(char*)malloc(sizeof(char));
	        cin_patient=(char*)malloc(sizeof(char));
     	  	fscanf(f,"%s %s %s %s %s %d",nom,ville,cin,etat,cin_patient,&age);
     	  	d=CreerDonnees(cin,nom,ville,age);
     	  	p->etat=etat;
     	  	p->cin_patient=cin_patient;
     	  	p->info=d;
     	  	p->suivant_ct=debut;
     	  	debut=p;	
	      } 
		debut=debut->suivant_ct;  	
	 }
   return debut; 
}

//la fonction qui va ajouter un contact
contact* AjouterContact(char *cin,char *nomc,char *ville,int age,char *etat,contact *debut,char *cin_patient){
   contact *p;
   donnees *d=(donnees*)malloc(sizeof(donnees));
   p=(contact*)malloc(sizeof(contact));
   
   d=CreerDonnees(cin,nomc,ville,age);
   p->info=d;
   p->etat=etat;
   p->cin_patient=cin_patient;
   if(debut==NULL)
     {
     	debut=p;
     	p->suivant_ct=NULL;
	 }
	else
	  {
	    p->suivant_ct=debut;
		debut=p;	
	  } 
   return debut;
}


//la fonction qui ecrit la liste des contacts dans le fichier
void ecrire_fichier_contact(contact *debut){
	contact *p;
	FILE *f;
	f=fopen("Fichier_Contacts.txt","w");
	if(f!=NULL){
	 	p=debut;
	 	while(p!=NULL){
		   fprintf(f,"%s %s %s %s %s %d\n",p->info->nomc,p->info->ville,p->info->cin,p->etat,p->cin_patient,p->info->age);
		   p=p->suivant_ct;   		
		  }
	 }
	 fclose(f);
}

//la fonction qui affiche la liste des contacts
void Affichage_contact(contact *debut)
{
	contact *tmp=debut;    //tmp :pointeur temporaire
    while (tmp!=NULL){
        printf("[");
        printf("CIN: %s",tmp->info->cin);
        printf(" | Nom: %s",tmp->info->nomc);
        printf(" | Ville: %s",tmp->info->ville);
        printf(" | Age: %d",tmp->info->age);
        printf(" | CIN de patient: %s",tmp->cin_patient);
        tmp=tmp->suivant_ct;
        printf(" ]\n");
    }

    printf("\n\n\n");
}

//la fonction qui supprime un contact
contact* supprimer_contact(contact *debut,char *cin){
    contact *p,*q;
    p=debut;
    if(p==NULL)
      	printf("la liste est vide, on peut rien supprimer \n ");
    else{
		while(p!=NULL && strcmp(p->info->cin,cin)!=0){
		   	q=p;
		   	p=p->suivant_ct;
			} 
		}
  	if(p==NULL){
  	    printf("il n'y a pas de contact ayant ce cin %s \n",cin);
	}
	else{
		if(p==debut)            //c'est a dire que l'element a supprimer est le premier de la liste 
		debut=p->suivant_ct;
		else	        
		q->suivant_ct=p->suivant_ct;
		free(p);  	
		}
		return debut;  		
}

	
//la fonction qui modifie l'etat d'un contact pour qu'il soit un patient
contact *modifier_etat_contact(contact *debut,patient *pat,char *etat,char *cin){
	contact *p;
	FILE *f;
	p=debut;
	while(p!=NULL&&strcmp(p->info->cin,cin)!=0)
	  p=p->suivant_ct;
	if(p==NULL)
       printf("pas de contact ayant ce cin %s\n",cin);
    else{ 
    	pat=AjouterPatient(p->info->cin,p->info->nomc,p->info->ville,p->info->age,etat,pat);
    	debut=supprimer_contact(debut,cin);
	}
	
	return debut;	
}	

//la fonction qui va lister les contacts selon la ville
int lister_contact_selon_ville(contact *debut,char *nom_v){
	contact *p;
	int i=0;
	p=debut;	
	while(p!=NULL){
	 	if(strcmp(p->info->ville,nom_v)==0){
		   printf("[");
           printf("CIN : %s",p->info->cin);
           printf(" | Nom: %s",p->info->nomc);
           printf(" | Ville: %s",p->info->ville);
           printf(" | Age: %d",p->info->age);
           printf(" | CIN de patient: %s",p->cin_patient);
           printf(" ]\n");
		   i=1;	
		 }
	   p=p->suivant_ct;	
	 }
	return i; 
}

//la fonction qui affiche les contacts d'un patient
int lister_contact_patient(contact *debut,char *cin_patient){
	contact *p;
	int i=0;
	p=debut;	
	while(p!=NULL){
	 	if(strcmp(p->cin_patient,cin_patient)==0){
		   printf("[");
           printf("CIN: %s",p->info->cin);
           printf(" | Nom: %s",p->info->nomc);
           printf(" | Ville: %s",p->info->ville);
           printf(" | Age: %d",p->info->age);
           printf(" | CIN de patient: %s",p->cin_patient);
           printf(" ]\n");
		   i=1;	
		 }
	   p=p->suivant_ct;	
	 }
	return i; 
}

//la fonction qui liste le nombre des contacts par ville
int nbr_contact_ville(Ville *debut,contact *tete){
	contact *p;
	Ville *v;
	v=debut;
	int cpt;
	while(v!=NULL){  
	    cpt=0;
	 	p=tete;
	    while(p!=NULL){
	    	if(strcmp(p->info->ville,v->nom_ville)==0)
	    	   	cpt++;
	    	p=p->suivant_ct;   	
		 }
	    printf("le nombre des contacts de la ville %s est %d \n",v->nom_ville,cpt);	
		v=v->suivant;	
	 }
	 return cpt;	 
}

// La fonction qui calcule le taux de propagation des contacts
float taux_propagation_contact(Ville *v,contact *tete){
	contact *p;
	int cpt,total_contact;  
		cpt=0;
		total_contact=0;
		float taux;
	 	p=tete;
		while(p!=NULL){
			total_contact++; // nombre total des contacts
	    	p=p->suivant_ct; 
		}
		while(v!=NULL){
			cpt=cpt+v->nbr_h;
			v=v->suivant;
		}
		taux=(float)total_contact/cpt;
		taux=taux*100;

	return taux;	
}
