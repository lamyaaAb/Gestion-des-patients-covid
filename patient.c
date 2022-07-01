#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include "head.h"

//la fonction qui cree une donnee
donnees* CreerDonnees(char *cin,char *nomc,char *ville,int age)  
{
	donnees *d=(donnees*)malloc(sizeof(donnees));
	d->cin=(char*)malloc(sizeof(char));
	d->nomc=(char*)malloc(sizeof(char));
	d->ville=(char*)malloc(sizeof(char));
	if(d!=NULL)
	  {
	   strcpy(d->cin,cin);
	   strcpy(d->nomc,nomc);
	   strcpy(d->ville,ville);
	   d->age=age;	
	  }

	return d;
}

//la fonction qui cree la liste des villes
Ville* creerListV(Ville *debut)
{
	Ville *v;
	FILE *f;
	int nbr_h,nbr_litC,nbr_litR;
	char *nom_v;
	
    f=fopen("Fichier_Villes2.txt","r");
    if(f!=NULL)
     { 
        while(!feof(f))
     	  {
            v=(Ville*)malloc(sizeof(Ville));
            nom_v=(char*)malloc(sizeof(char));
     	  	fscanf(f,"%s %d %d %d",nom_v,&nbr_h,&nbr_litC,&nbr_litR);
     	  	v->nbr_h=nbr_h;
     	  	v->nbr_litC=nbr_litC;
     	  	v->nbr_litR=nbr_litR;
     	  	v->nom_ville=nom_v;
     	  	v->suivant=debut;
     	  	debut=v;	
	      } 	
	 }
   return debut; 
}

//la fonction qui cree la liste des patients
patient* creerListP(patient *debut)
{
	donnees *d;
	patient *p;
	FILE *f;
	int age,i;
	char *ville,*nom,*etat,*cin;
	
    f=fopen("Fichier_Patients2.txt","r");
    if(f!=NULL)
     { 
        while(!feof(f))
     	  {
     	  	d=(donnees*)malloc(sizeof(donnees));
            p=(patient*)malloc(sizeof(patient));
            nom=(char*)malloc(sizeof(char));
	        ville=(char*)malloc(sizeof(char));
	        cin=(char*)malloc(sizeof(char));
	        etat=(char*)malloc(sizeof(char));
     	  	fscanf(f,"%s %s %s %s %d",nom,ville,cin,etat,&age);
     	  	d=CreerDonnees(cin,nom,ville,age);
     	  	p->info=d;
     	  	p->etat=etat;
     	  	p->suivant=debut;
     	  	debut=p;	
	      } 
		debut=debut->suivant;  	
	 }
   return debut; 
}

//la fonction qui va ajouter un patient
patient* AjouterPatient(char *cin,char *nomc,char *ville,int age,char *etat,patient *debut)
{
   patient *p;
   donnees *d=(donnees*)malloc(sizeof(donnees));
   p=(patient*)malloc(sizeof(patient));
   
   d=CreerDonnees(cin,nomc,ville,age);
   p->info=d;
   //strcpy(p->etat,etat);
   p->etat=etat;
   if(debut==NULL)
     {
     	debut=p;
     	p->suivant=NULL;
	 }
	else
	  {
	    p->suivant=debut;
		debut=p;	
	  } 
   return debut;
}

//la fonction qui ecrit la liste des patients dans le fichier des patients
void ecrireFichier(patient *debut)
{
	patient *p;
	FILE *f;
	f=fopen("Fichier_Patients2.txt","w");
	if(f!=NULL)
	 {
	 	p=debut;
	 	while(p!=NULL)
	 	 {
		   fprintf(f,"%s %s %s %s %d\n",p->info->nomc,p->info->ville,p->info->cin,p->etat,p->info->age);
		   p=p->suivant;   		
		  }
		fclose(f);
	 }
}


//la fonction qui affiche la liste des patients

void Affichage(patient *debut)
{
	patient *tmp=debut;    //tmp :pointeur temporaire
    while (tmp!=NULL)
      {
        printf("[");
        printf("CIN: %s",tmp->info->cin);
        printf(" | Nom: %s",tmp->info->nomc);
        printf(" | Ville: %s",tmp->info->ville);
        printf(" | Etat: %s",tmp->etat);
        printf(" | Age: %d",tmp->info->age);
        tmp=tmp->suivant;
        printf(" ]\n");
      }

    printf("\n\n\n");
}
	
//la fonction qui modifie l'etat d'un patient
patient* modifierEtat(patient *debut,char *etat,char *cin)
{
	patient *p;
	p=debut;
	while(p!=NULL&&strcmp(p->info->cin,cin)!=0)
	  p=p->suivant;
	if(p==NULL)
       printf("pas de patient ayant ce cin %s \n",cin);
    else
	 	p->etat=etat;
   
	return debut;	
}	

//la fonction qui supprime un patient
patient* supprimerPatient(patient *debut,char *cin)
     {
       	patient *p,*q;

       	p=debut;
       	if(p==NULL)
       	   	printf("la liste est vide, on peut rien supprimer \n ");
       	else
		   {
		     	while(p!=NULL && strcmp(p->info->cin,cin)!=0)
		   	     {
		   	   	    q=p;
		   	        p=p->suivant;
			     } 
		   }
  	    if(p==NULL)
  	      {
  	      	printf("il n'y a pas de patient ayant ce cin %s\n",cin);
		  }
	    else
		  {
		  	if(p==debut)            //c'est a dire que l'element a supprimer est le premier de la liste 
		  	  	debut=p->suivant;
		    else	        
			  q->suivant=p->suivant;
			
			 free(p);  	
		  }
		return debut;  		
	 }

//la fonction qui va lister les patients selon la ville
int lister_selon_ville(patient *debut,char *nom_v)
{
	patient *p;
	int i=0;
	p=debut;
	
	while(p!=NULL)
	 {
	 	if(strcmp(p->info->ville,nom_v)==0)
		 {
		   printf("[");
           printf("CIN: %s",p->info->cin);
           printf(" | Nom: %s",p->info->nomc);
           printf(" | Ville: %s",p->info->ville);
           printf(" | Etat: %s",p->etat);
           printf(" | Age: %d",p->info->age);
           printf(" ]\n");
		   i=1;	
		 }
	   p=p->suivant;	
	 }
	return i; 
}

//la fonction qui va lister les patients selon l'etat
int lister_selon_etat(patient *debut,char *etat)  
{
	patient *p;     //cette fonction retourne un int juste pour traiter le cas ou on n'a pas de patient dans la ville donnee
	int i=0;       //autrement dit dans le main o va faire le test sur la valeur retourner par la fonction
	p=debut;       //si la valeur reste nulle c'est a dire qu'on a pas entre dans la boucle, du coup on n'a pas de patient ayant cet etat donne.
	
	while(p!=NULL)
	 {
	 	if(strcmp(p->etat,etat)==0)
		 {
		   printf("[ ");
           printf("CIN: %s",p->info->cin);
           printf(" | Nom: %s",p->info->nomc);
           printf(" | Ville: %s",p->info->ville);
           printf(" | Etat: %s",p->etat);
           printf(" | Age: %d",p->info->age);
           printf(" ]\n");
		   i=1;	
		 }
	   p=p->suivant;	
	 }
	return i; 
}
//la fonction qui liste le nombre de cas par ville
void nbr_cas_ville(Ville *debut,patient *tete)
{
	patient *p;
	Ville *v;
	v=debut;
	int cpt;
	while(v!=NULL)
	 {  
	    cpt=0;
	 	p=tete;
	    while(p!=NULL)
	     {
	    	if(strcmp(p->info->ville,v->nom_ville)==0)
	    	   	cpt++;
	    	p=p->suivant;   	
		 }
	    printf("le nombre des patients de la ville %s est %d \n",v->nom_ville,cpt);	
		v=v->suivant;	
	 }	 
}
//la fonction qui liste le nombre des cas critiques
int nbr_cas_critique(patient *debut)
{
	int cpt=0;
	patient *p;
	p=debut;
	while(p!=NULL)
	 {
		if(strcmp(p->etat,"critique")==0)
	       cpt++;
	    p=p->suivant;   
	 }
return cpt;	
}

//la fonction qui calcule le taux d'occupation des lits
float taux_occup_lit(Ville *tete,patient *debut)
{
	Ville *v;
	float taux;
	int cpt,somLits=0; 
	cpt=nbr_cas_critique(debut);      //somLit veut dire la somme de tous les lits que nous avons dans le fichier des villes   //cpt veut dire le nombre de cas critiques
	v=tete;
	                        //nous nous sommes basees sur le fait que les gens aujourd'hui qui ont etat normal nutilisent pas de lits
	while(v!=NULL)                //donc seules les personnes ayant etat critique utilisent les lits,\ et donc le nbr de lits est equivalent au nbr des cas critiques
	  {
	   somLits=somLits+v->nbr_litC; //ici on calcule le nbr total de lits dans tout le Maroc 
	   v=v->suivant;
	   } 
               
	taux=(float)cpt/somLits;
	taux=taux*100;
	return taux;
}

//la fonction qui donne la proportion des lits de reanimation occupes
float  proportion_lit_rean(Ville *tete,patient *debut)
{
	int nbr_cas_rean=0,somLitsR=0;
	float proportion;
	Ville *v;
	patient *p;
	p=debut;
	v=tete;
	while(p!=NULL)
	 {
	 	if(strcmp(p->etat,"reanimation")==0)
	 	  nbr_cas_rean++;
	 	p=p->suivant;	
	 }
	while(v!=NULL)
	 {
	 	somLitsR=somLitsR+v->nbr_litR;
	 	v=v->suivant;	
	 }
   proportion=(float)nbr_cas_rean/somLitsR;
   proportion=proportion*100;
   return proportion;	 
}

