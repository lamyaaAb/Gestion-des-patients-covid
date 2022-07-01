#include<string.h>
#include<stddef.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>



//les structures 
typedef struct donnees
 {
	char *nomc,*ville,*cin;  //nomc veut dire le nom complet
	int age; 
 }donnees;
 
 
typedef struct patient
{
	donnees *info;
    struct patient *suivant;
    char *etat;
 }patient;
 
 typedef struct Ville
 {
 	char *nom_ville;
 	int nbr_h;      // le nombre des habitants d'une ville
 	int nbr_litC;  // le nombre de lits pour les cas critiques 
 	int nbr_litR; // le nombre de lits pour les cas qui ont besoin d'aide respiratoire
 	struct Ville *suivant;
 }Ville;
 
 typedef struct gueri
{
	donnees *info;
    struct gueri *suivant;
    char *jour;    //le jour de la confirmation que la personne n'est plus malade 
 }gueri;


 typedef struct deces
{
	donnees *info;
    struct deces *suivant;
    char *jour;    //le jour ou  la personne a mouru  
 }deces; 
 
// structure qui permet la déclaration la liste des contacts 
typedef struct contact{
	donnees *info;
    struct contact *suivant_ct; // suivant de contact
    char *etat;     // etat par defaut est contact
    char *cin_patient; // cin de patient contacter
}contact;
 
 //***************************************************************************************les fonctions pour la partie des patients
 //la fonction qui cree une donnee
donnees* CreerDonnees(char *cin,char *nomc,char *ville,int age); 
//la fonction qui cree la liste des ville ze3ma qui va recuperer a partie du fichier concernat les villes 
Ville* creerListV(Ville *debut);
//la fonction qui cree la liste des personnes ze3ma qui va recuperer du fichier
patient* creerListP(patient *debut);
//la fonction qui va ajouter un patient
patient* AjouterPatient(char *cin,char *nomc,char *ville,int age,char *etat,patient *debut);
//la fonction qui ecrit la liste des patients dans le fichier des patients
void ecrireFichier(patient *debut);
//la fonction qui affiche la liste des patients
void Affichage(patient *debut);
//la fonction qui modifie l'etat d'un patient
patient* modifierEtat(patient *debut,char *etat,char *cin);
//la fonction qui supprime un patient
patient* supprimerPatient(patient *debut,char *cin);
//la fonction qui va lister les patients selon la ville
int lister_selon_ville(patient *debut,char *nom_v);
//la fonction qui va lister les patients selon l'etat
int lister_selon_etat(patient *debut,char *etat);
//la fonction qui liste le nombre de cas par ville
void nbr_cas_ville(Ville *debut,patient *tete);
//la fonction qui liste le nombre des cas critiques
int nbr_cas_critique(patient *debut);
//la fonction qui calcule le taux d'occupation des lits
float taux_occup_lit(Ville *tete,patient *debut);
//la fonction qui donne la proportion des lits de reanimation occupes
float proportion_lit_rean(Ville *tete,patient *debut);

//*************************************************************************************les fonctions pour la partie des gueris
//la fonction qui cree la liste des personnes ze3ma qui va recuperer du fichier
gueri* creerListG(gueri *debut);
//la fonction qui va ajouter un patient
gueri* AjouterGueri(char *cin,char *nomc,char *ville,int age,char *jour,gueri *debut,patient *tete);
//la fonction qui ecrit la liste des gueris dans le fichier des gueris
void ecrireFichierG(gueri *debut);
//la fonction qui affiche la liste des gueris
void AffichageG(gueri *debut);
//la fonction qui modifie les informations d'un gueri
gueri* modifierG(gueri *debut,char *nom,char *ville,int age,char *jour,char *cin);
//la fonction qui supprime un gueri
gueri* supprimerGueri(gueri *debut,char *cin);
//la fonction qui va lister les gueris selon la ville
int listerG_selon_ville(gueri *debut,char *nom_v);
//la fonction qui liste le nombre des gueris par ville
void nbr_Gueri_ville(Ville *debut,gueri *tete);
//la fonction qui retourne le taux de guerison par jour 
float taux_guerison(gueri *tete,patient *debut,char *jour);
//la fonction qui retourne le taux total des gueris
float taux_total_guerison(gueri *tete,patient *debut);

//****************************************************************************************les fonctions pour la partie des deces
//la fonction qui cree la liste des deces a partir  du fichier
deces* creerListD(deces *debut);
//la fonction qui va ajouter un decede
deces* AjouterDecede(char *cin,char *nomc,char *ville,int age,char *jour,deces *debut, patient *tete);
//la fonction qui ecrit la liste des deces dans le fichier des deces
void ecrireFichierD(deces *debut);
//la fonction qui affiche la liste des deces
void AffichageD(deces *debut);
//la fonction qui supprime un decede
deces* supprimerDecede(deces *debut,char *cin);
//la fonction qui va lister les deces selon la ville
int listerD_selon_ville(deces *debut,char *nom_v);
//la fonction qui liste le nombre des deces par ville
void nbr_Deces_ville(Ville *debut,deces *tete);
//la fonction qui retourne le taux de deces par jour 
float taux_deces(deces *tete,patient *debut,char *jour);
//la fonction qui retourne le taux de deces par jour et par ville 
float taux_deces_JV(deces *tete,patient *debut,char *jour,char *ville);
//la fonction qui retourne le taux total des deces  
float taux_total_deces(deces *tete,patient *debut);

//****************************************************************************************les fonctions pour la partie des contacts


//creer la liste des contacts
contact* creerListC(contact *debut);
//la fonction qui va ajouter un contact
contact* AjouterContact(char *cin,char *nomc,char *ville,int age,char *etat,contact *debut,char *cin_patient);
//la fonction qui ecrit la liste des contacts dans le fichier
void ecrire_fichier_contact(contact *debut);
//la fonction qui affiche la liste des contacts
void Affichage_contact(contact *debut);
//la fonction qui modifie l'etat d'un contact pour qu'il soit un patient
contact *modifier_etat_contact(contact *debut,patient *pat,char *etat,char *cin);
//la fonction qui supprime un contact
contact* supprimer_contact(contact *debut,char *cin);
//la fonction qui va lister les contacts selon la ville
int lister_contact_selon_ville(contact *debut,char *nom_v);
//la fonction qui liste le nombre des contacts par ville
int nbr_contact_ville(Ville *debut,contact *tete);
// La fonction qui calcule le taux de propagation des contacts
float taux_propagation_contact(Ville *v,contact *tete);
//la fonction qui affiche les contacts d'un patient
int lister_contact_patient(contact *debut,char *cin_patient);
//****************************************************************************************les fonctions des menus
int menu_principal();
int menu_patient();
int menu_contact();
int menu_gueri();
int menu_deces();
donnees *Saisir_donnee();


