#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LGMAXNOM 30
#define LGMAXPRENOM 20
#define LGMAXMAIL 254

// Type structuré pour stocker une date de naissance
struct sDate
{
	unsigned char Jour;
	unsigned char Mois;
	unsigned short int Annee;
};

// Type structuré pour stocker un contact dans une liste simplement chaînée
struct sContact
{
	char Nom[LGMAXNOM+1];
	char Prenom[LGMAXPRENOM+1];
	char Mail[LGMAXMAIL+1];
	struct sDate Naissance;
	struct sContact *pSuivant; // Adresse du contact suivant
};

// Type structuré permettant d'accéder à une liste chaînée de contacts 
struct sRepertoire
{ 
	struct sContact *Debut; // Adresse du premier contact de la liste
	struct sContact *Fin; // Adresse du dernier contact de la liste
};

// Type permettant de manipuler un répertoire
typedef struct sRepertoire *tRepertoire;

/* Affichage des informations d'un contact (version 1)
* Entrée : 
*    - Contact : le contact
*/
void AfficherContact1(struct sContact Contact) {
	printf("[---------------]\n%s\n%s\n%s\n%02d/%02d/%d\n===============\n",
		Contact.Nom,
		Contact.Prenom,
		Contact.Mail,
		Contact.Naissance.Jour,
		Contact.Naissance.Mois,
		Contact.Naissance.Annee
	);
}

/* Affichage des informations d'un contact (version 2)
* Entrée : 
*     - pContact : adresse du contact
*/  
void AfficherContact2(const struct sContact *pContact) {
		printf("[---------------]\n%s\n%s\n%s\n%02d/%02d/%d\n===============\n",
		pContact->Nom,
		pContact->Prenom,
		pContact->Mail,
		pContact->Naissance.Jour,
		pContact->Naissance.Mois,
		pContact->Naissance.Annee
	);
}  

/* Création d'un répertoire vide
* Valeur de retour : accès au répertoire vide alloué de manière dynamique
*/
tRepertoire CreerRepertoire(void) {
	struct sRepertoire * rep = calloc(1, sizeof(struct sRepertoire));
	if (rep == NULL) {
		perror("OMG");
		return NULL;
	}
	return rep;
}

/* Affichage de tous les contacts d'un répertoire
* Entrée :
*   - Repertoire : accès au répertoire
*/
void AfficherRepertoire(tRepertoire Repertoire) {
	printf("\x1b[96m------[ REPERTOIRE ]------\n\x1b[0m");

	if (Repertoire->Debut == NULL) {
		printf("    VIDEUH\n");
		printf("\x1b[96m--------------------------\n\x1b[0m");

		return;
	}

	struct sContact * suivant = Repertoire->Debut;

	while (suivant != NULL) {
		AfficherContact2(suivant);

		suivant = suivant->pSuivant;
	}

	printf("\x1b[96m--------------------------\n\x1b[0m");
}

static void copyStr(char * source, char * destination) {int i=0;while(source[i]!='\0'){destination[i]=source[i];i++;};}

/* Ajout d'un contact à la fin d'un répertoire
* Entrée : 
*    - pNouveau : adresse du contact à ajouter
* Mise à jour (entrée et sortie):
*    - Repertoire : accès au répertoire
*/
void AjouterContact(struct sContact *pNouveau, tRepertoire Repertoire) {
	struct sContact * nouv = calloc(1, sizeof(struct sContact));
	if (nouv == NULL) {
		perror("OMG");
		return;
	}

	nouv->Naissance = pNouveau->Naissance;
	nouv->pSuivant = pNouveau->pSuivant;

	copyStr(pNouveau->Mail, nouv->Mail);
	copyStr(pNouveau->Nom, nouv->Nom);
	copyStr(pNouveau->Prenom, nouv->Prenom);

	if (Repertoire->Debut == NULL) {
		Repertoire->Debut = nouv;
		Repertoire->Fin = nouv;
	} else {
		Repertoire->Fin->pSuivant = nouv;
		Repertoire->Fin = nouv;
	}
}

/* Recherche d'un contact par son nom
* Entrées :
*    - NomRecherche : nom recherché (chaîne de caractères)
*    - Repertoire : accès au répertoire
* Valeur retournée : adresse du contact trouvé ou NULL si le contact est absent
*/
struct sContact * Rechercher(char NomRecherche[], tRepertoire Repertoire) {
	struct sContact * contact = Repertoire->Debut;

	while (contact != NULL) {
		if (strcmp(contact->Nom, NomRecherche) == 0) return contact;

		contact = contact->pSuivant;
	}

	return NULL;
}

/* Écriture de tous les contacts d'un répertoire dans un fichier au format binaire
* Entrées :
*    - Repertoire : accès au répertoire
*    - NomFichier : nom du fichier (chaîne de caractères)
*/
void EcrireFichier(tRepertoire Repertoire, char NomFichier[]) {
	FILE * stream = fopen(NomFichier, "wb");

	struct sContact * contact = Repertoire->Debut;
	while (contact != NULL) {
		fwrite(contact, sizeof(struct sContact), 1, stream);
		contact = contact->pSuivant;
	}

	fclose(stream);
}

/* Lecture d'un répertoire dans un fichier au format binaire
* Entrée :
*    - NomFichier : nom du fichier (chaîne de caractères)
* Valeur de retour : accès au répertoire créé ou NULL en cas de problème
*/
tRepertoire LireFichier(char NomFichier[]) {
	tRepertoire rep = CreerRepertoire();
	if (rep == NULL) {
		perror("OMG");
		return rep;
	}

	FILE * stream = fopen(NomFichier, "rb");
	if (stream == NULL) {
		perror("OMG 2");
		free(rep);
		return rep;
	}

	struct sContact contact;

	while (fread(&contact, sizeof(struct sContact), 1, stream) > 0) {
		AjouterContact(&contact, rep);
	}

	return rep;
}

/* Libération de tout l'espace mémoire occupé par un répertoire
* et mise à NULL de l'accès au répertoire
* Mise à jour (entrée et sortie) : 
*    - pRepertoire : adresse de l'accès à un répertoire
*/
void LibererRepertoire(tRepertoire *pRepertoire) {
	struct sContact * contact = (*pRepertoire)->Debut;
	while (contact != NULL) {	
		struct sContact * suivant = contact->pSuivant;
		free(contact);

		contact = suivant;
	}

	free(*pRepertoire);
	*pRepertoire = NULL;
}


int main(void) {
	// Trois contacts
	struct sContact
	c1 = {"KARENA","Emma","emma.karena@legria.es",{1,5,2001},NULL },
	c2 = {"DEUF","John","john.deuf@mayonnaise.fr",{12,1,1999},NULL },
	c3 = {"MANVUSSA","Gerard","gerard.manvussa@etonnant.com",{24,11,2000},NULL };
	
	printf("\x1b[94m***** Création du répertoire.\n\x1b[0m");
	tRepertoire Rep = CreerRepertoire();
	
	printf("\x1b[94m***** Ajout de trois contacts.\n\x1b[0m");
	AjouterContact(&c1,Rep);
	AjouterContact(&c2,Rep);
	AjouterContact(&c3,Rep);
	printf("\x1b[94m***** Répertoire initial :\n\x1b[0m");
	AfficherRepertoire(Rep);
	
	// Contact supplémentaire
	struct sContact Nouv = {"AMBOLAGE", "Oscar", "oscar.ambolage@latele.com", {9,6,2002}, NULL };

	printf("\x1b[94m***** Ajout d'un contact.\n\x1b[0m");
	AjouterContact(&Nouv,Rep);
	printf("\x1b[94m***** Répertoire après ajout :\n\x1b[0m");
	AfficherRepertoire(Rep);
	
	char Nom[]="DEUF"; // Nom qui va être recherché
	printf("\n\x1b[94m***** Recherche de %s :\n\x1b[0m",Nom);
	struct sContact *Res=Rechercher(Nom,Rep);

	if (Res==NULL) printf("%s n'est pas dans le repertoire.\n",Nom);
	else AfficherContact2(Res);
	
	char Fichier[]="repertoire2.dat"; // Nom du fichier binaire
	printf("\n\x1b[94m***** Écriture du répertoire dans le fichier %s.\x1b[0m\n",Fichier);
	EcrireFichier(Rep,Fichier);
	printf("\n\x1b[94m***** Lecture du répertoire depuis le fichier %s.\x1b[0m\n",Fichier);
	tRepertoire RepLu=LireFichier("repertoire2.dat");
	printf("\x1b[94m***** Répertoire lu :\n\x1b[0m");
	AfficherRepertoire(RepLu);
	
	printf("\n\x1b[94m***** Libération des répertoires.\n\x1b[0m");
	LibererRepertoire(&Rep);  
	LibererRepertoire(&RepLu);
	
	return 0;
}
