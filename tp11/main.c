#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LGMAXNOM 30
#define LGMAXPRENOM 20
#define LGMAXMAIL 254
#define LGMAXREP 64

// Type structuré pour stocker une date de naissance
struct sDate
{
	unsigned char Jour;
	unsigned char Mois;
	unsigned short int Annee;
};

// Type structuré pour stocker un contact
struct sContact
{
	char Nom[LGMAXNOM+1];
	char Prenom[LGMAXPRENOM+1];
	char Mail[LGMAXMAIL+1];
	struct sDate Naissance;
};


/* Affichage des informations d'un contact (version 1)
* Entrée : 
*    - Contact : le contact
*/
void AfficherContact1(struct sContact Contact) {
	printf("[--------------------]\n%s\n%s\n%s\n%02d/%02d/%d\n]--------------------[\n",
		Contact.Nom,
		Contact.Prenom,
		Contact.Mail,
		Contact.Naissance.Jour,
		Contact.Naissance.Mois,
		Contact.Naissance.Annee
	);
	// Remarque : %02d signifie entier sur 2 caractères avec ajout éventuel d'un 0 à gauche
}  

/* Affichage des informations d'un contact (version 2)
* Entrée : >
*     - pContact : adresse du contact
*/  
void AfficherContact2(const struct sContact *pContact) {
	printf("[--------------------]\n%s\n%s\n%s\n%02d/%02d/%d\n]--------------------[\n",
		pContact->Nom,
		pContact->Prenom,
		pContact->Mail,
		pContact->Naissance.Jour,
		pContact->Naissance.Mois,
		pContact->Naissance.Annee
	);
}

/* Affichage de tous les contacts d'un répertoire
* Entrées :
*   - Repertoire : tableau de contacts
*   - NbContacts : nombre de contacts
*/
void AfficherRepertoire(struct sContact Repertoire[], int NbContacts) {
	int i = 0;
	while (i < NbContacts) {
		AfficherContact2(&(Repertoire[i]));
		i++;
	}
}

/* Ajout d'un contact à la fin d'un répertoire
* Entrée : 
*    - pNouveau : adresse du contact à ajouter
* Mises à jour (entrées et sorties):
*    - Repertoire : tableau de contacts 
*    - pNbContact : adresse du nombre de contacts
*/
void AjouterContact(struct sContact * pNouveau, struct sContact Repertoire[], int * pNbContacts) {
	if (*pNbContacts == LGMAXREP) {
		perror("Impossible d'ajouter un contact");
		return;
	}
	Repertoire[(*pNbContacts)] = *pNouveau;
	*(pNbContacts)+=1;
}

/* Recherche d'un contact par son nom
* Entrées :
*    - NomRecherche : nom recherché (chaîne de caractères)
*    - Repertoire : tableau de contacts 
*    - NbContacts : nombre de contacts
* Valeur retournée : indice du contact dans le tableau ou -1 si le contact est
* absent
*/
int Rechercher(char NomRecherche[], struct sContact Repertoire[], int NbContacts) {
	int index = 0;
	while (index < NbContacts) {
		if (strcmp(Repertoire[index].Nom, NomRecherche) == 0) return index;
		index++;
	}
	return -1;
}

/* Écriture de tous les contacts d'un répertoire dans un fichier au format binaire
* Entrées :
*    - Repertoire : tableau de contacts 
*    - NbContacts : nombre de contacts
*    - NomFichier : nom du fichier (chaîne de caractères)
*/
void EcrireFichier(struct sContact Repertoire[], int NbContacts, char NomFichier[]) {
	FILE * stream = fopen(NomFichier, "wb");
	if (stream == NULL) {
		perror("EcrireFichier : OMG");
		return;
	}

	// int index = 0;
	// while (index < NbContacts) {
	// 	int a, b, c, d;
	// 	struct sContact contact = Repertoire[index];

	// 	char buffer[LGMAXMAIL + 1] = {0};

	// 	sprintf(buffer, "%s\n", contact.Nom);
	// 	a = fwrite(buffer, sizeof(char), LGMAXNOM, stream);

	// 	sprintf(buffer, "%s\n", contact.Prenom);
	// 	b = fwrite(buffer, sizeof(char), LGMAXPRENOM, stream);

	// 	sprintf(buffer, "%s\n", contact.Mail);
	// 	c = fwrite(buffer, sizeof(char), LGMAXMAIL, stream);

	// 	sprintf(buffer, "%02d%02d%d\n", contact.Naissance.Jour, contact.Naissance.Mois, contact.Naissance.Annee);
	// 	d = fwrite(buffer, sizeof(char), 9, stream);

	// 	if (a == EOF || b == EOF || c == EOF || d == EOF) {
	// 		perror("EcrireFichier : OMG 2");
	// 		return;
	// 	}

	// 	index++;
	// }
	fwrite(Repertoire, sizeof(struct sContact), NbContacts, stream);

	fclose(stream);
}

/* Lecture d'un répertoire dans un fichier au format binaire
* Version 1 : lecture contact par contact
* Entrée :
*    - NomFichier : nom du fichier (chaîne de caractères)
* Sortie :
*    - Repertoire : tableau de contacts 
* Valeur de retour : nombre de contacts lus
*/
int LireFichier1(struct sContact Repertoire[], char NomFichier[]) {
	FILE * stream = fopen(NomFichier, "rb");
	if (stream == NULL) {
		perror("OMG");
		return -1;
	}

	int index = 0;
	while (fread(&Repertoire[index], sizeof(struct sContact), 1, stream)) {
		index++;
	}
	return index;
}

/* Lecture d'un répertoire dans un fichier au format binaire
* Version 2 : une seule lecture de tous les contacts après calcul du nombre de 
* contacts
* Entrée :
*    - NomFichier : nom du fichier (chaîne de caractères)
* Sortie :
*    - Repertoire : tableau de contacts 
* Valeur de retour : nombre de contacts lus
*/
int LireFichier2(struct sContact Repertoire[], char NomFichier[]) {
	FILE * stream = fopen(NomFichier, "rb");
	if (stream == NULL) {
		perror("OMG");
		return -1;
	}
	fseek(stream, 0, SEEK_END);
	long taille = ftell(stream);

	int elements = taille / sizeof(struct sContact);
	fread(Repertoire, sizeof(struct sContact), elements, stream);

	return elements;
}

/* Fonction de comparaison de deux contacts pour le tri d'un tableau de contact 
* par ordre lexicographique, croissant des noms
* Entrées : 
*    - pc1 : adresse du premier contact
*    - pc2 : adresse du second contact
* Valeur de retour : entier supérieur, égal ou inférieur à 0, selon que le nom
* du premier contact est supérieur, égal ou inférieur au nom du second contact
*/
int CompareContacts(const void *pc1, const void *pc2) {
	return strcmp(((struct sContact * )pc1)->Nom, ((struct sContact *)pc2)->Nom);
}


int main(void) {
	// Répertoire initialisé avec trois contacts 
	struct sContact Rep[LGMAXREP] = {
		{"KARENA","Emma","emma.karena@legria.es", {1,5,2001} },
		{"DEUF","John","john.deuf@mayonnaise.fr", {12,1,1999} },
		{"MANVUSSA","Gerard","gerard.manvussa@etonnant.com", {24,11,2000} }
	};
	int NbContacts=3;

	printf("\x1b[94m***** Répertoire initial :\n\x1b[0m");
	AfficherRepertoire(Rep,NbContacts);

	// Contact supplémentaire
	struct sContact Nouv = {
		"AMBOLAGE",
		"Oscar",
		"oscar.ambolage@latele.com",
		{9,6,2002}
	};

	printf("\x1b[94m***** Ajout d'un contact.\n\x1b[0m");
	AjouterContact(&Nouv,Rep,&NbContacts);

	printf("\x1b[94m***** Répertoire après ajout :\n\x1b[0m");
	AfficherRepertoire(Rep,NbContacts);
	
	char Nom[]="DEUF"; // Nom qui va être recherché
	printf("\n\x1b[94m***** Recherche de %s :\n\x1b[0m",Nom);

	int Ind=Rechercher(Nom,Rep,NbContacts);
	if (Ind==-1)
	printf("%s n'est pas dans le repertoire.\n\x1b[0m",Nom);
	else
	AfficherContact2(&(Rep[Ind]));
	
	char Fichier[]="repertoire.dat"; // Nom du fichier binaire
	printf("\n\x1b[94m***** Écriture du répertoire dans le fichier %s.\n\x1b[0m",Fichier);
	EcrireFichier(Rep,NbContacts,Fichier);
	
	struct sContact RepLu[LGMAXREP]; // Nouveau répertoire
	int NbContactsLus;
	
	printf("\n\x1b[94m***** Lecture du répertoire depuis le fichier %s (v1).\n\x1b[0m",Fichier);
	NbContactsLus=LireFichier1(RepLu,"repertoire.dat");
	printf("\x1b[94m***** Répertoire lu :\n\x1b[0m");
	AfficherRepertoire(RepLu,NbContactsLus);
	
	printf("\n\x1b[94m***** Lecture du répertoire depuis le fichier %s (v2).\n\x1b[0m",Fichier);
	NbContactsLus=LireFichier2(RepLu,"repertoire.dat");
	printf("\x1b[94m***** Répertoire lu :\n\x1b[0m");
	AfficherRepertoire(RepLu, NbContactsLus);
	
	printf("\n\x1b[94m***** Tri du répertoire lu.\n\x1b[0m");
	printf("\x1b[94m***** Répertoire trié :\n\x1b[0m");
	
	qsort(RepLu, NbContactsLus, sizeof(struct sContact), CompareContacts);	

	AfficherRepertoire(RepLu,NbContactsLus);
	
	return 0;
}
