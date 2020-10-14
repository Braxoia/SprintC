/////////////////////////////////////////////////
/// \file source.c
/// 
/// \brief Le sprint 2 du projet.
/// 
/// Le but de ce sprint est de garder en mémoire
/// les informations des différents entités
/// et d'afficher leurs informations via les
/// instructions.
///
/////////////////////////////////////////////////

// Headers 
/////////////////////////////////////////////////   
#pragma warning(disable:4996) // Pour désactiver l'erreur concernant scanf
#include <stdio.h> // Pour l'utilisation de printf et scanf
#include <stdlib.h> // Pour l'utilisation de atoi
#include <string.h> // Pour l'utilisation de strcmp et de strncpy

// Messages emis par les instructions
/////////////////////////////////////////////////   
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n" ///< Sortie de l'instruction commande
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n" ///< Sortie de l'instruction tache
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n" ///< Sortie de l'instruction progression
#define MSG_PASSE "## une reallocation est requise\n" ///< Sortie de l'instruction passe
#define MSG_SPECIALITES "specialites traitees : " ///< Sortie de l'instruction specialites 
#define MSG_TRAVAILLEURS "la specialite %s peut etre prise en charge par : " ///< Sortie de l'instruction travailleurs 
#define MSG_CLIENT "le client %s a commande : " ///< Sortie de l'instruction client 
#define MSG_CLIENT_TOUS "le client %s a commande : " ///< Sortie de l'instruction client version tous 
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n" ///< Sortie de l'instruction superivision 
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n" ///< Sortie de l'instruction charge 
#define MSG_INTERRUPTION "## fin de programme\n" ///< Sortie de l'instruction interruption 

// Lexemes
/////////////////////////////////////////////////   
/// \brief Type pour les booléens
typedef enum
{
	FAUX = 0, ///< Valeur fausse
	VRAI = 1  ///< Valeur vraie
} Booleen;

Booleen EchoActif = FAUX; ///< Si vrai, l'echo est actif

#define LGMOT 35 ///< La taille maximale d'un mot
#define NBCHIFFREMAX 5 ///< La taille maximale d'un chiffre
typedef char Mot[LGMOT + 1]; ///< Contient les entrées de l'utilisateur

// Données
/////////////////////////////////////////////////   
#define MAX_SPECIALITES 10 ///< Le nombre maximal de spécialités
#define MAX_TRAVAILLEURS 50 ///< Le nombre maximal de travailleurs
#define MAX_CLIENTS 100 ///< Le nombre maximal de clients

/////////////////////////////////////////////////
///	\brief Structure représentant une spécialité.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Mot nom; ///< Nom de la specialité
	int cout_horaire; ///< Coût horaire de la spécialité
} Specialite;

/////////////////////////////////////////////////
///	\brief Structure représentant toutes les
/// specialites.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Specialite tab_specialites[MAX_SPECIALITES]; ///< Tableau contenant toutes les spécialités
	unsigned int nb_specialites; ///< Nombre de spécialité developpée
} Specialites;

/////////////////////////////////////////////////
///	\brief Structure représentant un travailleur.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Mot nom; ///< Nom du travailleur
	Booleen tags_competences[MAX_SPECIALITES]; ///< Tableau pour savoir dans quelle spécialité exerce le travailleur
} Travailleur;

/////////////////////////////////////////////////
///	\brief Structure représentant tous les
/// travailleurs.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Travailleur tab_travailleurs[MAX_TRAVAILLEURS]; ///< Tableau contenant tous les travailleurs
	unsigned int nb_travailleurs; ///< Nombre de travailleur embauché
} Travailleurs;

/////////////////////////////////////////////////
///	\brief Structure représentant tous les 
/// clients.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Mot tab_clients[MAX_CLIENTS]; ///< Tableau contenant tous les clients
	unsigned int nb_clients; ///< Nombre de client 
} Clients;

//	Prototypes des fonctions 
/////////////////////////////////////////////////
// Lexemes
void get_id(Mot id);
int get_int();

// Utilitaires
unsigned int get_indice(const Specialites* specialites, const Mot nom_specialite);
void print_travailleurs(const Travailleurs* travailleurs, const Mot nom_specialite, const unsigned int indice_specialite);

// Instructions
void traite_developpe(Specialites* specialites);
void traite_embauche(const Specialites* specialites, Travailleurs* travailleurs);
void traite_demarche(Clients* clients);
void traite_progression();
void traite_passe();
void traite_commande();
void traite_tache();
void traite_specialites(const Specialites* specialites);
void traite_travailleurs(const Specialites* specialites, Travailleurs* travailleurs);
void traite_client(const Clients* clients);
void traite_supervision();
void traite_charge();
void traite_interruption();

/////////////////////////////////////////////////
///	\brief Boucle principale.
/// 
/// Gère les instructions entrées par 
/// l'utilisateur.
/// 
/// \param argc Nombre d'arguments
/// \param argv Arguments: "echo" permet un retour
/// à l'écran de ce qu'on écrit via scanf
/// 
/// \return Etat du programme
/// 
/////////////////////////////////////////////////   
int main(int argc, char* argv[])
{
	if (argc >= 2 && strcmp("echo", argv[1]) == 0)
	{
		EchoActif = VRAI;
	}

	Specialites specialites;
	specialites.nb_specialites = 0;

	Travailleurs travailleurs;
	travailleurs.nb_travailleurs = 0;

	Clients clients;
	clients.nb_clients = 0;

	Mot buffer; // Les instructions principales
	while (VRAI)
	{
		get_id(buffer);
		if (strcmp(buffer, "developpe") == 0) // strcmp() compare deux chaines; égaux si 0
		{
			traite_developpe(&specialites);
			continue;
		}
		else if (strcmp(buffer, "embauche") == 0)
		{
			traite_embauche(&specialites, &travailleurs);
			continue;
		}
		else if (strcmp(buffer, "demarche") == 0)
		{
			traite_demarche(&clients);
			continue;
		}
		else if (strcmp(buffer, "commande") == 0)
		{
			traite_commande(&clients);
			continue;
		}
		else if (strcmp(buffer, "tache") == 0)
		{
			traite_tache();
			continue;
		}
		else if (strcmp(buffer, "progression") == 0)
		{
			traite_progression();
			continue;
		}
		else if (strcmp(buffer, "passe") == 0)
		{
			traite_passe();
			continue;
		}
		else if (strcmp(buffer, "specialites") == 0)
		{
			traite_specialites(&specialites);
			continue;
		}
		else if (strcmp(buffer, "travailleurs") == 0)
		{
			traite_travailleurs(&specialites, &travailleurs);
			continue;
		}
		else if (strcmp(buffer, "client") == 0)
		{
			traite_client(&clients);
			continue;
		}
		else if (strcmp(buffer, "supervision") == 0)
		{
			traite_supervision();
			continue;
		}
		else if (strcmp(buffer, "charge") == 0)
		{
			traite_charge();
			continue;
		}
		else if (strcmp(buffer, "interruption") == 0)
		{
			traite_interruption();
			break;
		}

		printf("!!! instruction inconnue >%s< !!!\n", buffer);
	}

	return 0;
	system("pause");
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction developpe.
/// 
/// Récupère le nom de la spécialité et son coût
/// horaire.
/// 
/// Garde en mémoire la nouvelle spécialité dans
/// un tableau.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// 
/////////////////////////////////////////////////   
void traite_developpe(Specialites* specialites)
{
	Mot nom_specialite;
	get_id(nom_specialite);

	int cout_horaire = get_int();

	Specialite specialite;
	strncpy(specialite.nom, nom_specialite, LGMOT);
	specialite.cout_horaire = cout_horaire;

	specialites->tab_specialites[specialites->nb_specialites++] = specialite;
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction embauche.
/// 
/// Récupère le nom du travailleur ainsi que 
/// la specialite dans laquelle il va exercer.
/// 
/// Garde en mémoire le nouveau travailleur
/// dans un tableau. 
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param travailleurs Pointeur sur la structure
/// représentant tous les travailleurs.
/// 
///////////////////////////////////////////////// 
void traite_embauche(const Specialites* specialites, Travailleurs* travailleurs)
{
	Mot nom_specialite, nom_travailleur;

	get_id(nom_travailleur);
	get_id(nom_specialite);

	Booleen exist = FAUX;

	unsigned int i = 0;
	for (i = 0; i < travailleurs->nb_travailleurs; ++i)
	{
		if (strcmp(travailleurs->tab_travailleurs[i].nom, nom_travailleur) == 0)
		{
			exist = VRAI;
			travailleurs->tab_travailleurs[i].tags_competences[get_indice(specialites, nom_specialite)] = VRAI;

			break;
		}
	}

	if (exist == FAUX)
	{
		Travailleur travailleur; // Variable temporaire pour plus de lisibilité
		strncpy(travailleur.nom, nom_travailleur, LGMOT);
		travailleur.tags_competences[get_indice(specialites, nom_specialite)] = VRAI;

		travailleurs->tab_travailleurs[travailleurs->nb_travailleurs++] = travailleur; // On insère le nouveau travailleur dans le tableau
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction demarche.
/// 
/// Récupère le nom du client entré.
/// 
/// Garde en mémoire le nouveau client dans un 
/// tableau.
/// 
/// \param clients Pointeur sur la structure 
/// représentant tous les clients.
/// 
///////////////////////////////////////////////// 
void traite_demarche(Clients* clients)
{
	Mot nom_client;
	get_id(nom_client);

	strncpy(clients->tab_clients[clients->nb_clients++], nom_client, LGMOT);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction commande.
/// 
/// Récupère le nom de la commande et le client.
/// 
/// Affiche le nom du client et le nom de la 
/// à effectuer.
/// 
///////////////////////////////////////////////// 
void traite_commande()
{
	Mot nom_commande, nom_client;

	get_id(nom_commande);
	get_id(nom_client);

	printf(MSG_COMMANDE, nom_commande, nom_client);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction tache.
/// 
/// Récupère le nom de la commande, sa spécialité
/// et le nombre d'heures pour effectuer la tache.
/// 
/// Affiche la commande, la spécialité associée
/// et le nombre d'heures nécessaires pour 
/// effectuer la tâche de la spécialité.
/// 
///////////////////////////////////////////////// 
void traite_tache()
{
	Mot nom_specialite, nom_commande;

	get_id(nom_commande);
	get_id(nom_specialite);

	int nombre_heures = get_int();

	printf(MSG_TACHE, nom_commande, nom_specialite, nombre_heures);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction progression. 
///
/// Récupère le nom de la commande, la spécialité
/// et le nombre d'heures à ajouter à son 
/// avancement.
/// 
/// Affiche le nombre d'heure réalisée pour une
/// spécialité d'une commande en particulier.
/// 
///////////////////////////////////////////////// 
void traite_progression()
{
	Mot nom_commande, nom_specialite;

	get_id(nom_commande);
	get_id(nom_specialite);

	int nombre_heures = get_int();

	printf(MSG_PROGRESSION, nom_commande, nom_specialite, nombre_heures);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction passe.
/// 
/// Réaffecte la tâche.
/// 
///////////////////////////////////////////////// 
void traite_passe()
{
	printf(MSG_PASSE);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction spécialites.
/// 
/// Affiche la liste de toutes les specialités 
/// existantes.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// 
///////////////////////////////////////////////// 
void traite_specialites(const Specialites* specialites)
{
	printf(MSG_SPECIALITES);

	unsigned int i = 0;
	for (i = 0; i < specialites->nb_specialites; ++i)
	{
		if (i != 0)
		{
			printf(", ");
		}

		printf("%s/%d", specialites->tab_specialites[i].nom, specialites->tab_specialites[i].cout_horaire);
	}

	printf("\n");
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction travailleurs.
/// 
/// Récupère la spécialité pour lequel afficher
/// ses travailleurs, ou "tous" pour toutes les
/// spécialités.
/// 
/// Affiche la liste de tous les travailleurs 
/// existants ou tous les travailleurs d'une 
/// specialité en particulier.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param travailleurs Pointeur sur la structure
/// représentant tous les travailleurs.
/// 
///////////////////////////////////////////////// 
void traite_travailleurs(const Specialites* specialites, Travailleurs* travailleurs)
{
	Mot nom_specialite;
	get_id(nom_specialite);

	if (strcmp(nom_specialite, "tous") == 0)
	{
		for (unsigned int indice = 0; indice < specialites->nb_specialites; ++indice)
		{
			print_travailleurs(travailleurs, specialites->tab_specialites[indice].nom, indice);
		}
	}
	else
	{
		print_travailleurs(travailleurs, nom_specialite, get_indice(specialites, nom_specialite));
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction client.
/// 
/// Récupère le nom du client pour lequel afficher
/// ses commandes, ou "tous" pour tous les
/// clients.
/// 
/// Affiche la liste de toutes les commandes 
/// effectuées par tous les clients ou pour un
/// client en particulier.
/// 
/// \param clients Pointeur sur la structure 
/// représentant tous les clients.
/// 
///////////////////////////////////////////////// 
void traite_client(const Clients* clients)
{
	Mot nom_client;
	get_id(nom_client);

	if (strcmp(nom_client, "tous") == 0) // Pour tous les clients
	{
		unsigned int i = 0;
		for (i = 0; i < clients->nb_clients; ++i)
		{
			printf(MSG_CLIENT_TOUS, clients->tab_clients[i]);
			printf("\n");
		}
	}
	else
	{
		unsigned int i = 0;
		for (i = 0; i < clients->nb_clients; ++i)
		{
			if (strcmp(nom_client, clients->tab_clients[i]) == 0)
			{
				printf(MSG_CLIENT, nom_client);
				printf("\n");
			}
		}
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction supervision.
/// 
/// Affiche la progression de toutes les 
/// commandes.
/// 
///////////////////////////////////////////////// 
void traite_supervision()
{
	printf(MSG_SUPERVISION);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction charge.
/// 
/// Récupère le nom du travailleur pour lequel on
/// veut afficher sa charge de travail.
/// 
/// Affiche la charge de travail d'un travailleur
/// donné.
/// 
///////////////////////////////////////////////// 
void traite_charge()
{
	Mot nom_travailleur;
	get_id(nom_travailleur);

	printf(MSG_CHARGE, nom_travailleur);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction interruption.
/// 
/// Met fin au programme.
/// 
/////////////////////////////////////////////////  
void traite_interruption()
{
	printf(MSG_INTERRUPTION);
}

/////////////////////////////////////////////////
///	\brief Afficher les travailleurs possèdant
/// une compétence en particulier.
/// 
/// \param travailleurs Pointeur sur la structure
/// représentant tous les travailleurs.
/// \param nom_specialite Le nom de la spécialité 
/// pour laquelle on veut afficher les
/// travailleurs l'exercant.
/// \param indice_specialite L'indice de la 
/// spécialité pour laquelle on veut afficher les
/// travailleurs l'exercant.
/// 
///////////////////////////////////////////////// 
void print_travailleurs(const Travailleurs* travailleurs, const Mot nom_specialite, const unsigned int indice_specialite)
{
	printf(MSG_TRAVAILLEURS, nom_specialite);

	Booleen first = VRAI;

	unsigned int i = 0;
	for (i = 0; i < travailleurs->nb_travailleurs; ++i) // Parcourir tous les travailleurs
	{
		if (travailleurs->tab_travailleurs[i].tags_competences[indice_specialite] == VRAI) // S'il possède la spécialité
		{
			if (first)
			{
				first = FAUX;
			}
			else
			{
				printf(", ");
			}

			printf("%s", travailleurs->tab_travailleurs[i].nom);
		}
	}

	printf("\n");
}

/////////////////////////////////////////////////
///	\brief Récupérer l'indice d'une spécialité
/// dans le tableau contenant les spécialités.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param nom_specialite Le nom de la spécialité 
/// pour lequel on veut récuperer l'indice.
/// 
///////////////////////////////////////////////// 
unsigned int get_indice(const Specialites* specialites, const Mot nom_specialite)
{
	unsigned int indice;
	for (indice = 0; indice < specialites->nb_specialites; ++indice)
	{
		if (strcmp(specialites->tab_specialites[indice].nom, nom_specialite) == 0)
		{
			break;
		}
	}

	return indice;
}

/////////////////////////////////////////////////
///	\brief Récupérer les entrées de l'utilisateur.
/// 
/// \param id Le mot entrée
/// 
/////////////////////////////////////////////////   
void get_id(Mot id)
{
	scanf("%s", id);

	if (EchoActif)
	{
		printf(">>echo %s\n", id);
	}
}

/////////////////////////////////////////////////
///	\brief Récupérer l'entrée puis le convertir 
/// en un entier.
/// 
/// \return L'entier récupéré
/// 
/////////////////////////////////////////////////  
int get_int()
{
	char buffer[NBCHIFFREMAX + 1];
	scanf("%s", buffer);

	if (EchoActif)
	{
		printf(">>echo %s\n", buffer);
	}

	return atoi(buffer);
}
