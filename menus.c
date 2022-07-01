#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include "head.h"

donnees* saisir_donnee(){
	int age;
	patient *p;
	char* cin=(char*)malloc(sizeof(char));
	char* etat=(char*)malloc(sizeof(char));
	char* nomc=(char*)malloc(sizeof(char));
	char* ville=(char*)malloc(sizeof(char));
	printf("\nDonnez le code cin: ");
	scanf("%s",cin);
	printf("Donnez le nom : ");
	scanf("%s",nomc);
	printf("Donnez la ville : ");
	scanf("%s",ville);
	printf("Donnez l'age: ");
	scanf("%d",&age);
	donnees *d=CreerDonnees(cin,nomc,ville,age);
	return d;
}
/* ------------------------------ Menus ---------------------------- */
int menu_principal(){
	int choix;
	system("cls");
	printf("\n\n");
	printf("    ***************************************************************\n");
    printf("    *         Gestion citoyens-patients de covid19                *\n");
	printf("    ***************************************************************\n");
	printf("    *\t    1. Gestions des patients                              *\n");
	printf("    *\t    2. Gestions des contacts                              *\n");
	printf("    *\t    3. Gestions des gueris                                *\n");
	printf("    *\t    4. Gestions des deces                                 *\n");
	printf("    *\t    0. Quitter le programme                               *\n");
	printf("    ***************************************************************\n");
	printf("     \t\t    Donnez votre choix : ");
	scanf("%d",&choix);
	printf("    ***************************************************************\n");
	printf("\n\n\n");
	system("cls");
	return choix;
}

int menu_patient(){
	int choix;
	system("cls");
	printf("\n\n");
	printf("    ***************************************************************\n");
    printf("    *         Gestion des patients de covid19                     *\n");
	printf("    ***************************************************************\n");
	printf("    *\t    1. Ajouter un patient                                 *\n");
	printf("    *\t    2. Modifier l'etat d'un patient                       *\n");
	printf("    *\t    3. Supprimer un patient                               *\n");
	printf("    *\t    4. Afficher la liste des patients                     *\n");
	printf("    *\t    5. lister les patients selon la ville                 *\n");
	printf("    *\t    6. lister les patients selon l'etat                   *\n");
	printf("    *\t    7. Nombre des patients par ville                      *\n");
	printf("    *\t    8. Nombre des cas critiques                           *\n");
	printf("    *\t    9. Taux d'occupation des lits                         *\n");
	printf("    *\t   10. Proportion de lits de reanimation occupees         *\n");
	printf("    *\t    0. Retourner au menu principal                        *\n");
	printf("    ***************************************************************\n");
	printf("     \t\t    Donnez votre choix : ");
	scanf("%d",&choix);
	printf("    ***************************************************************\n");
	printf("\n\n\n");
	system("cls");
	return choix;
}

int menu_contact(){
	int choix;
	system("cls");
	printf("\n\n");
	printf("    ***************************************************************\n");
    printf("    *         Gestion des contacts des patients de covid19        *\n");
	printf("    ***************************************************************\n");
	printf("    *\t    1. Ajouter un contact                                 *\n");
	printf("    *\t    2. Modifier l'etat d'un contact                       *\n");
	printf("    *\t    3. Supprimer un contact                               *\n");
	printf("    *\t    4. Afficher la liste des contacts                     *\n");
	printf("    *\t    5. lister les contacts selon la ville                 *\n");
	printf("    *\t    6. Lister les contacts des patients                   *\n");
	printf("    *\t    7. Nombre total des contacts                          *\n");
	printf("    *\t    8. Taux de propagation                                *\n");
	printf("    *\t    0. Retourner au menu principal                        *\n");
	printf("    ***************************************************************\n");
	printf("     \t\t    Donnez votre choix : ");
	scanf("%d",&choix);
	printf("    ***************************************************************\n");
	printf("\n\n\n");
	system("cls");
	return choix;
}

int menu_gueri(){
	int choix;
	system("cls");
	printf("\n\n");
	printf("    ***************************************************************\n");
    printf("    *         Gestion des gueris  de covid19                      *\n");
	printf("    ***************************************************************\n");
	printf("    *\t    1. Ajouter un gueri                                   *\n");
	printf("    *\t    2. Modifier un gueri                                  *\n");
	printf("    *\t    3. Supprimer un gueri                                 *\n");
	printf("    *\t    4. Afficher la liste des gueris                       *\n");
	printf("    *\t    5. lister les gueris selon la ville                   *\n");
	printf("    *\t    6. Nombre total des gueris par ville                  *\n");
	printf("    *\t    7. Taux de guerison par jour                          *\n");
	printf("    *\t    8. Taux total de guerison                             *\n");
	printf("    *\t    0. Retourner au menu principal                        *\n");
	printf("    ***************************************************************\n");
	printf("     \t\t    Donnez votre choix : ");
	scanf("%d",&choix);
	printf("    ***************************************************************\n");
	printf("\n\n\n");
	system("cls");
	return choix;
}

int menu_deces(){
	int choix;
	system("cls");
	printf("\n\n");
	printf("    ***************************************************************\n");
    printf("    *         Gestion des deces  de covid19                       *\n");
	printf("    ***************************************************************\n");
	printf("    *\t    1. Ajouter un deces                                   *\n");
	printf("    *\t    2. Supprimer un deces                                 *\n");
	printf("    *\t    3. Afficher la liste des deces                        *\n");
	printf("    *\t    4. lister les deces selon la ville                    *\n");
	printf("    *\t    5. Nombre total des deces par ville                   *\n");
	printf("    *\t    6. Taux de deces par jour                             *\n");
	printf("    *\t    7. Taux de deces par jour et par ville                *\n");
	printf("    *\t    8. Taux total de deces                                *\n");
	printf("    *\t    0. Retourner au menu principal                        *\n");
	printf("    ***************************************************************\n");
	printf("     \t\t    Donnez votre choix : ");
	scanf("%d",&choix);
	printf("    ***************************************************************\n");
	printf("\n\n\n");
	system("cls");
	return choix;
}

