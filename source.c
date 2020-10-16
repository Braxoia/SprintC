/////////////////////////////////////////////////
/// \file source.c
/// 
/// \brief Le sprint 3 du projet.
/// 
/// Le but de ce sprint est de garder en mémoire
/// les commandes des clients puis d'implémenter 
/// leur affichage.
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
#define MSG_SPECIALITES "specialites traitees : " ///< Sortie de l'instruction specialites 
#define MSG_TRAVAILLEURS "la specialite %s peut etre prise en charge par : " ///< Sortie de l'instruction travailleurs 
#define MSG_CLIENT "le client %s a commande : " ///< Sortie de l'instruction client 
#define MSG_SUPERVISION "etat des taches pour %s : " ///< Sortie de l'instruction supervision 
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
#define MAX_COMMANDES 500 ///< Le nombre maximal de commandes

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

/////////////////////////////////////////////////
///	\brief Structure représentant une tâche.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	unsigned int nb_heures_requises; ///< Nombre d'heures requises pour effectuer la tâche
	unsigned int nb_heures_effectuees; ///< Nombre d'heures effectuées
} Tache;

/////////////////////////////////////////////////
///	\brief Structure représentant une commande.
/// 
///////////////////////////////////////////////// 
typedef struct
{
	Tache taches_par_specialite[MAX_SPECIALITES];  // nb_heures_requises == 0 <=> pas de tache pour cette specialite
	Mot nom_commande; ///< Nom de la commande
	unsigned int idx_client; ///< Indice du client auquel appartient la commande
} Commande;

/////////////////////////////////////////////////
///	\brief Structure représentant toutes les 
/// commandes.
/// 
/////////////////////////////////////////////////
typedef struct
{
	Commande tab_commandes[MAX_COMMANDES]; ///< Tableau contenant toutes les commandes
	unsigned int nb_commandes; ///< Nombre de commandes effectuées
} Commandes;

//	Prototypes des fonctions 
/////////////////////////////////////////////////
// Lexemes
void get_id(Mot id);
int get_int();

// Utilitaires
const unsigned int get_indice_specialite(const Specialites* specialites, const Mot nom_specialite);
const unsigned int get_indice_commande(const Commandes* commandes, const Mot nom_commandes);
const unsigned int get_indice_client(const Clients* clients, const Mot nom_client);
void print_travailleurs(const Travailleurs* travailleurs, const Mot nom_specialite, const unsigned int indice_specialite);
void print_commandes(const Commandes* commandes, const Mot nom_client, const unsigned int indice_client);

// Instructions
void traite_developpe(Specialites* specialites);
void traite_embauche(const Specialites* specialites, Travailleurs* travailleurs);
void traite_demarche(Clients* clients);
void traite_progression(const Specialites* specialites, Commandes* commandes);
void traite_passe();
void traite_commande(const Clients* clients, Commandes* commandes);
void traite_tache(const Specialites* specialites, Commandes* commandes);
void traite_specialites(const Specialites* specialites);
void traite_travailleurs(const Specialites* specialites, const Travailleurs* travailleurs);
void traite_client(const Clients* clients, const Commandes* commandes);
void traite_supervision(const Specialites* specialites, const Commandes* commandes);
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

	Commandes commandes;
	commandes.nb_commandes = 0;

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
			traite_commande(&clients, &commandes);
			continue;
		}
		else if (strcmp(buffer, "tache") == 0)
		{
			traite_tache(&specialites, &commandes);
			continue;
		}
		else if (strcmp(buffer, "progression") == 0)
		{
			traite_progression(&specialites, &commandes);
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
			traite_client(&clients, &commandes);
			continue;
		}
		else if (strcmp(buffer, "supervision") == 0)
		{
			traite_supervision(&specialites, &commandes);
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

	unsigned int indice_travailleur;
	for (indice_travailleur = 0; indice_travailleur < travailleurs->nb_travailleurs; ++indice_travailleur)
	{
		if (strcmp(travailleurs->tab_travailleurs[indice_travailleur].nom, nom_travailleur) == 0)
		{
			travailleurs->tab_travailleurs[indice_travailleur].tags_competences[get_indice_specialite(specialites, nom_specialite)] = VRAI;

			return;
		}
	}

	Travailleur* travailleur = &travailleurs->tab_travailleurs[travailleurs->nb_travailleurs++]; // Le nouveau travailleur 
	strncpy(travailleur->nom, nom_travailleur, LGMOT);
	travailleur->tags_competences[get_indice_specialite(specialites, nom_specialite)] = VRAI;
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
/// Insère la nouvelle commande dans le tableau
/// contenant toutes les commandes.
/// 
/// \param clients Pointeur sur la structure 
/// représentant tous les clients.
/// \param commandes Pointeur sur la structure 
/// représentant toutes les commandes.
/// 
///////////////////////////////////////////////// 
void traite_commande(const Clients* clients, Commandes* commandes)
{
	Mot nom_commande, nom_client;

	get_id(nom_commande);
	get_id(nom_client);

	Commande commande; // Variable temporaire pour plus de lisibilité

	unsigned int indice_specialite;
	for (indice_specialite = 0; indice_specialite < MAX_SPECIALITES; ++indice_specialite) // Initialiser les heures requises
	{
		commande.taches_par_specialite[indice_specialite].nb_heures_requises = 0;
		commande.taches_par_specialite[indice_specialite].nb_heures_effectuees = 0;
	}

	commande.idx_client = get_indice_client(clients, nom_client); // Indice du client

	strncpy(commande.nom_commande, nom_commande, LGMOT);
	commandes->tab_commandes[commandes->nb_commandes++] = commande; // On insère la nouvelle commande dans le tableau
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction tache.
/// 
/// Récupère le nom de la commande, sa spécialité
/// et le nombre d'heures pour effectuer la tache.
/// 
/// Affecte à la commande une nouvelle tâche en 
/// indiquant le nombre d'heures requises.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param commandes Pointeur sur la structure 
/// représentant toutes les commandes.
/// 
///////////////////////////////////////////////// 
void traite_tache(const Specialites* specialites, Commandes* commandes)
{
	Mot nom_specialite, nom_commande;

	get_id(nom_commande);
	get_id(nom_specialite);

	int heures_requises = get_int();

	commandes->tab_commandes[get_indice_commande(commandes, nom_commande)]
		.taches_par_specialite[get_indice_specialite(specialites, nom_specialite)]
		.nb_heures_requises = heures_requises;
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction progression. 
///
/// Récupère le nom de la commande, la spécialité
/// et le nombre d'heures à ajouter à son 
/// avancement.
/// 
/// Met à jour la progression d'une tâche  
/// en ajoutant des heures effectuées.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param commandes Pointeur sur la structure 
/// représentant toutes les commandes.
/// 
///////////////////////////////////////////////// 
void traite_progression(const Specialites* specialites, Commandes* commandes)
{
	Mot nom_commande, nom_specialite;

	get_id(nom_commande);
	get_id(nom_specialite);

	int heures_effectuees = get_int();

	commandes->tab_commandes[get_indice_commande(commandes, nom_commande)]
		.taches_par_specialite[get_indice_specialite(specialites, nom_specialite)]
		.nb_heures_effectuees += heures_effectuees;
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction passe.
/// 
/// Réaffecte la tâche.
/// 
///////////////////////////////////////////////// 
void traite_passe()
{
	// Cette instruction n'a aucun effet.
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

	unsigned int indice_specialite;
	for (indice_specialite = 0; indice_specialite < specialites->nb_specialites; ++indice_specialite)
	{
		if (indice_specialite != 0)
		{
			printf(", ");
		}

		printf("%s/%d", specialites->tab_specialites[indice_specialite].nom, specialites->tab_specialites[indice_specialite].cout_horaire);
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
void traite_travailleurs(const Specialites* specialites, const Travailleurs* travailleurs)
{
	Mot nom_specialite;
	get_id(nom_specialite);

	if (strcmp(nom_specialite, "tous") == 0)
	{
		unsigned int indice_travailleur;
		for (indice_travailleur = 0; indice_travailleur < specialites->nb_specialites; ++indice_travailleur)
		{
			print_travailleurs(travailleurs, specialites->tab_specialites[indice_travailleur].nom, indice_travailleur);
		}
	}
	else
	{
		print_travailleurs(travailleurs, nom_specialite, get_indice_specialite(specialites, nom_specialite));
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
/// \param commandes Pointeur sur la structure
/// représentant toutes les commandes.
/// 
///////////////////////////////////////////////// 
void traite_client(const Clients* clients, const Commandes* commandes)
{
	Mot nom_client;
	get_id(nom_client);

	if (strcmp(nom_client, "tous") == 0)
	{
		unsigned int indice_client;
		for (indice_client = 0; indice_client < clients->nb_clients; ++indice_client)
		{
			print_commandes(commandes, clients->tab_clients[indice_client], indice_client);
		}
	}
	else
	{
		print_commandes(commandes, nom_client, get_indice_client(clients, nom_client));
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction supervision.
/// 
/// Affiche la progression de toutes les 
/// commandes.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param travailleurs Pointeur sur la structure
/// représentant toutes les commandes.
/// 
///////////////////////////////////////////////// 
void traite_supervision(const Specialites* specialites, const Commandes* commandes)
{
	unsigned int indice_commande;
	for (indice_commande = 0; indice_commande < commandes->nb_commandes; ++indice_commande)
	{
		printf(MSG_SUPERVISION, commandes->tab_commandes[indice_commande].nom_commande);

		Booleen first = VRAI;
		
		unsigned int indice_specialite;
		for (indice_specialite = 0; indice_specialite < MAX_SPECIALITES; ++indice_specialite) // Afficher les tâches
		{
			if (commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_requises != 0)
			{
				if (first)
				{
					first = FAUX;
				}
				else
				{
					printf(", ");
				}

				printf("%s:%d/%d",
					specialites->tab_specialites[indice_specialite].nom,
					commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_effectuees,
					commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_requises);
			}
		}

		printf("\n");
	}
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
/// \param commandes Pointeur sur la structure
/// représentant toutes les commandes.
/// \param nom_client Le nom du client pour  
/// lequel on veut afficher ses commandes.
/// \param indice_client L'indice du client pour
/// lequel on veut afficher ses commandes.
/// 
///////////////////////////////////////////////// 
void print_commandes(const Commandes* commandes, const Mot nom_client, const unsigned int indice_client)
{
	printf(MSG_CLIENT, nom_client);

	Booleen first = VRAI;

	unsigned int indice_commande;
	for (indice_commande = 0; indice_commande < commandes->nb_commandes; ++indice_commande) // Afficher les commandes
	{
		if (commandes->tab_commandes[indice_commande].idx_client == indice_client)
		{
			if (first)
			{
				first = FAUX;
			}
			else
			{
				printf(", ");
			}

			printf("%s", commandes->tab_commandes[indice_commande].nom_commande);
		}
	}

	printf("\n");
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

	unsigned int indice_travailleur;
	for (indice_travailleur = 0; indice_travailleur < travailleurs->nb_travailleurs; ++indice_travailleur) // Parcourir tous les travailleurs
	{
		if (travailleurs->tab_travailleurs[indice_travailleur].tags_competences[indice_specialite] == VRAI) // S'il possède la spécialité
		{
			if (first)
			{
				first = FAUX;
			}
			else
			{
				printf(", ");
			}

			printf("%s", travailleurs->tab_travailleurs[indice_travailleur].nom);
		}
	}

	printf("\n");
}

/////////////////////////////////////////////////
///	\brief Récupérer l'indice d'une spécialité
/// dans le tableau contenant les spécialités.
/// 
/// \param commandes Pointeur sur la structure
/// représentant toutes les commandes.
/// \param nom_commande Le nom de la commande 
/// pour laquelle on veut récuperer l'indice.
/// 
///////////////////////////////////////////////// 
const unsigned int get_indice_commande(const Commandes* commandes, const Mot nom_commandes)
{
	unsigned int indice;
	for (indice = 0; indice < commandes->nb_commandes; ++indice)
	{
		if (strcmp(commandes->tab_commandes[indice].nom_commande, nom_commandes) == 0)
		{
			break;
		}
	}

	return indice;
}

/////////////////////////////////////////////////
///	\brief Récupérer l'indice d'une spécialité
/// dans le tableau contenant les spécialités.
/// 
/// \param clients Pointeur sur la structure
/// représentant tous les clients.
/// \param nom_client Le nom du client pour 
/// lequel on veut récuperer l'indice.
/// 
///////////////////////////////////////////////// 
const unsigned int get_indice_client(const Clients* clients, const Mot nom_client)
{
	unsigned int indice;
	for (indice = 0; indice < clients->nb_clients; ++indice)
	{
		if (strcmp(clients->tab_clients[indice], nom_client) == 0)
		{
			break;
		}
	}

	return indice;
}

/////////////////////////////////////////////////
///	\brief Récupérer l'indice d'une spécialité
/// dans le tableau contenant les spécialités.
/// 
/// \param specialites Pointeur sur la structure
/// représentant toutes les spécialités.
/// \param nom_specialite Le nom de la spécialité 
/// pour laquelle on veut récuperer l'indice.
/// 
///////////////////////////////////////////////// 
const unsigned int get_indice_specialite(const Specialites* specialites, const Mot nom_specialite)
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
