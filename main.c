#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include "head.h"



int main(){
	int choix,choix_patient,choix_gueri,choix_deces,choix_contact;
	char *cin, *nomc, *ville,*etat,*jour,*cin_patient;
    int age,i,cpt;
    float taux;
    donnees *d;
   	Ville *LV=NULL;   
    LV=creerListV(LV);   //LV veut dire la liste des villes
    patient *List=NULL;
	List=creerListP(List);  // List est le pointeur qui pointe sur le  debut de la liste des patients
	gueri *LG=NULL;
    deces *LD=NULL;        //LD signifie la liste des deces
    LD=creerListD(LD);
    LG=creerListG(LG);    //LG signifie la liste des guerisons
    contact *contct=NULL;   //contct signifie la liste des contacts
	contct=creerListC(contct);
	do{
	choix=menu_principal();
	switch(choix){
		case 1:
				do{
					choix_patient=menu_patient();
					switch(choix_patient){
						case 1: printf("\nAjouter Patient : \n");
								d=(donnees*)malloc(sizeof(donnees));
								d=saisir_donnee();
								etat=(char*)malloc(sizeof(char));
								printf("Donnez l'etat de patient : ");
								scanf("%s",etat);
							    List=AjouterPatient(d->cin,d->nomc,d->ville,d->age,etat,List);
							    getch();
						break;
						case 2: printf("\nModifier Patient :\n");
								etat=(char*)malloc(sizeof(char));
							    cin=(char*)malloc(sizeof(char));
							    printf("donner le cin et le nouvel etat : ");
							    scanf("%s %s",cin,etat);
							    List=modifierEtat(List,etat,cin);
							    getch();
						break;
						case 3: printf("\nSupprimer Patient :\n");
								cin=(char*)malloc(sizeof(char));
							    printf("donner le cin du patient a supprimer : ");
							    scanf("%s",cin);
							    List=supprimerPatient(List,cin);
							    getch();
						break;
						case 4: printf("\nAfficher Patient :\n");
								Affichage(List);
								getch();
						break;
						case 5: printf("\nLister les patients selon la ville :\n");
								ville=(char*)malloc(sizeof(char));
							    printf("donner la ville : ");
							    scanf("%s",ville);
								int i=lister_selon_ville(List,ville);
							    if(i==0)
							       printf("il n y a pas de patients dans cette ville %s \n",ville);
							    getch();   
						break;
						case 6: printf("\nLister les patients selon l'etat :\n");
								etat=(char*)malloc(sizeof(char));   
							    printf("donner l'etat : ");
							    scanf("%s",etat); 
								i=lister_selon_etat(List,etat);
								if(i==0)
							       printf("il n y a pas de patients ayant cet etat %s \n",etat);
							    getch();  
						break;
						case 7: printf("\nNombre des patients par ville :\n");
								nbr_cas_ville(LV,List);
								getch();
						break;
						case 8: printf("\nNombre des cas critiques :\n");
								cpt=nbr_cas_critique(List);
								printf("le nombre de patient ayant une etat critique est %d \n",cpt);
								getch();
						break;
						case 9: printf("\nTaux d'occupation des lits :\n");
								taux=taux_occup_lit(LV,List);
								printf("le taux d'occupation des lits est %.4f\n",taux);
								getch(); 
						break;
						case 10: printf("\nTaux d'occupation des lits  de reanimation :\n");
								taux=proportion_lit_rean(LV,List);
								printf("le taux d'occupation des lits de reanimation est %.4f\n",taux);
								getch();
						break;
						case 0:  break;
						default: printf("choix invalide \n");
					}
				}while(choix_patient!=0);
		break;
		
		case 2:
		       do{
				choix_contact=menu_contact();
				switch(choix_contact){
					case 1: printf("\nAjouter Contact :\n");
							d=(donnees*)malloc(sizeof(donnees));
							etat=(char*)malloc(sizeof(char));
							cin_patient=(char*)malloc(sizeof(char));
							d=saisir_donnee();
							printf("Donnez l'etat de contact : ");
							scanf("%s",etat);
							printf("Donnez le cin de patient contacte : ");
							scanf("%s",cin_patient);
						    contct=AjouterContact(d->cin,d->nomc,d->ville,d->age,etat,contct,cin_patient);
						    getch();
					break;
					case 2: printf("\nModifier Contact :\n");
							etat=(char*)malloc(sizeof(char));
						    cin=(char*)malloc(sizeof(char));
						    printf("donner le cin et le nouvel etat : ");
						    scanf("%s %s",cin,etat);
						    contct=modifier_etat_contact(contct,List,etat,cin);
						    getch();
					break;
					case 3: printf("\nSupprimer Contact :\n");
							cin=(char*)malloc(sizeof(char));
							printf("donner le cin du contact a supprimer : ");
						    scanf("%s",cin);
						    contct=supprimer_contact(contct,cin);
						    getch();
					break;
					case 4: printf("\nAfficher contact :\n");
							Affichage_contact(contct);
							getch();
					break;
					case 5: printf("\nLister les contacts selon la ville :\n");
							ville=(char*)malloc(sizeof(char));
						    printf("donner la ville : ");
						    scanf("%s",ville);
							i=lister_contact_selon_ville(contct,ville);
						    if(i==0)
						       printf("il n y a pas des contacts dans cette ville %s \n",ville);
						    getch();   
					break;
					case 6: printf("\nLister les contacts des patients :\n");
							cin_patient=(char*)malloc(sizeof(char));
						    printf("donner le cin du patient : ");
						    scanf("%s",cin_patient);
							i=lister_contact_patient(contct,cin_patient);
						    if(i==0)
						       printf("il n y a pas des contacts de ce patient %s\n",cin_patient);
						    getch();   
					break;
					case 7: printf("\nNombre des contacts par ville :\n");
							nbr_contact_ville(LV,contct);
							getch();
					break;
					case 8: printf("\nTaux de propagation des contacts :\n");
							taux=taux_propagation_contact(LV,contct);
							printf("le taux de propagation des contacts est %f\n",taux); 
							getch();
					break;
					case 0:
					break;
					default: printf("choix invalide \n");
				}
			}while(choix_contact!=0);
		break;
		
		case 3:
			   do{
			   	    choix_gueri=menu_gueri();
			   	    switch(choix_gueri){ 
			   	    case 1:
			   	    	    printf("\n Ajouter un gueri\n");
			   	    	    d=saisir_donnee();
			   	    	    jour=(char*)malloc(sizeof(char));
			   	    	    printf("donner le jour ou la personne a gueri : ");
			   	    	    scanf("%s",jour);
			   	    	    LG=AjouterGueri(d->cin,d->nomc,d->ville,d->age,jour,LG,List);  
			   	    	    getch();
			   	    break;
			   	    case 2:
			   	    	    printf("\n Modifier les informations d'un gueri\n");
			   	    	    d=saisir_donnee();
			   	    	    jour=(char*)malloc(sizeof(char));
			   	    	    printf("donner le jour ou la personne a gueri : ");
			   	    	    scanf("%s",jour);
			   	    	    LG=modifierG(LG,d->nomc,d->ville,d->age,jour,d->cin);
			   	    	    getch();
			   	    	  
			   	    break;
			   	    case 3:
			   	    	    printf("\n Supprimer un gueri\n");
			   	    	    cin=(char*)malloc(sizeof(char));
			   	    	    printf("donner le cin du gueri a supprimer : ");
			   	    	    scanf("%s",cin);
			   	    	    LG=supprimerGueri(LG,cin);
			   	    	    getch();
			   	    	   
			   	    break;
			   	    case 4:
			   	    	    printf("\n Afficher la liste des gueris\n");
			   	    	    cin=(char*)malloc(sizeof(char));
			   	    	    AffichageG(LG);
			   	    	    getch(); 
			   	    break;
			   	    case 5:
			   	    	    printf("\n Lister les gueris selon une ville\n");
			   	    	    ville=(char*)malloc(sizeof(char));
			   	    	    printf("donner la ville pour laquelle vous voulez consulter la liste des gueris : ");
			   	    	    scanf("%s",ville);
			   	    	    i=listerG_selon_ville(LG,ville);
			   	    	    if(i==0)
			   	    	      printf("il n y a pas de gueris dans cette ville %s \n ",ville);
			   	    	    getch();  
			   	    break;
			   	    case 6:
			   	    	    printf("\n Lister le nombre des gueris par ville \n");
			   	    	    nbr_Gueri_ville(LV,LG);
							getch();   	  
			   	    break;
			   	    case 7:
			   	    	    printf("\n Detemination du taux des gueris pour un jour donne \n");
			   	    	    jour=(char*)malloc(sizeof(char));
			   	    	    printf("donner le jour pour lequel vous voulez savoir le taux des gueris : ");
			   	    	    scanf("%s",jour);
			   	    	    taux=taux_guerison(LG,List,jour);
							printf("le taux des gueris pour le jour %s est %.4f \n",jour,taux);
							getch();		   
			   	    break;
			   	    case 8:
			   	    	    printf("\n Detemination du taux total des gueris \n");
			   	    	    taux=taux_total_guerison(LG,List);
							printf("le taux total des gueris est %.4f \n",taux);
							getch();		   
			   	    break;
			   	    
			   	    case 0: break;
			   	    default: printf("choix invalide \n");
			      }
			     }while(choix_gueri!=0);
		break;
		
		case 4:
			  do{
			        choix_deces=menu_deces();
			        switch(choix_deces){
			       	case 1:
			       		    printf("\n Ajouter un decede \n");
			   	    	    d=saisir_donnee();
			   	    	    jour=(char*)malloc(sizeof(char));
			   	    	    printf("donner le jour ou la personne a mourru : ");
			   	    	    scanf("%s",jour);
			       		    LD=AjouterDecede(d->cin,d->nomc,d->ville,d->age,jour,LD,List);
			       		    getch();
			       	break;	
			        case 2:
			        	    printf("\n Supprimer un decede \n");
			   	    	    cin=(char*)malloc(sizeof(char));
			   	    	    printf("donner le cin du decede a supprimer : ");
			   	    	    scanf("%s",cin);
			   	    	    LD=supprimerDecede(LD,cin);
							getch();   	
			       	break;
					case 3:
						    printf("\n Affichage de la liste des deces \n");
						    AffichageD(LD);
						    getch();
			       	break;
					case 4:
						    printf("\n Lister les deces selon une ville\n");
			   	    	    ville=(char*)malloc(sizeof(char));
			   	    	    printf("donner la ville pour laquelle vous voulez consulter la liste des deces : ");
			   	    	    scanf("%s",ville);
			   	    	    i=listerD_selon_ville(LD,ville);
			   	    	    if(i==0)
			   	    	      printf("il n y a pas de deces dans cette ville %s \n",ville);  
			   	    	    getch();  
			       	break;
					case 5:
						   printf("le nombre total des deces par ville \n");
						   nbr_Deces_ville(LV,LD);
						   getch();
			       	break;
					case 6:
						    printf("\n Detemination du taux des deces pour un jour donne \n");
			   	    	    jour=(char*)malloc(sizeof(char));
			   	    	    printf("donner le jour pour lequel vous voulez savoir le taux des deces : ");
			   	    	    scanf("%s",jour);
			   	    	    taux=taux_deces(LD,List,jour);
							printf("le taux des deces pour le jour %s est %.4f \n",jour,taux);
						    getch();	
			       	break;
			       	case 7:
						    printf("\n Detemination du taux des deces pour un jour et une ville donnee \n");
			   	    	    jour=(char*)malloc(sizeof(char));
			   	    	    ville=(char*)malloc(sizeof(char));
			   	    	    printf("donner le jour pour lequel vous voulez savoir le taux des deces : ");
			   	    	    scanf("%s",jour);
			   	    	    printf("donner la ville pour laquelle vous voulez savoir le taux des deces : ");
			   	    	    scanf("%s",ville);
			   	    	    taux=taux_deces_JV(LD,List,jour,ville);
							printf("le taux des deces pour le jour %s et pour la ville %s est %.4f \n",jour,ville,taux);
							getch();
			       	break;
			       	case 8:
						    printf("\n Detemination du taux total des deces\n");
			   	    	    taux=taux_total_deces(LD,List);
							printf("le taux total des deces est %.4f \n",taux);
							getch();
			       	break;
					case 0: break;
					default: printf("choix invalide \n");   	
				}
			   }while(choix_deces!=0);
		break;
		case 0: break;
		default: printf("choix invalide \n");	
	 }	
	}while(choix!=0);
	printf("vous avez choisi de quitter le programme \n");
	ecrireFichierD(LD);
	ecrireFichierG(LG);
	ecrireFichier(List);
	ecrire_fichier_contact(contct);
 
return 0;
}
