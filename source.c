/////////////////////////////////////////////////
///	\brief Headers
///
/////////////////////////////////////////////////  
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////
///	\brief Messages emis par les instructions
/// 
/////////////////////////////////////////////////   
#define MSG_DEVELOPPE "## nouvelle specialite \"%s\" ; cout horaire \"%d\"\n" 
#define MSG_EMBAUCHER "## nouveau travailleur \"%s\" competent pour la specialite \"%s\"\n"
#define MSG_DEMARCHE "## nouveau client \"%s\"\n"
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d�heures \"%d\")\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_PASSE "## une reallocation est requise\n"
#define MSG_SPECIALITES "## consultation des specialites\n" 
#define MSG_TRAVAILLEURS "## consultation des travailleurs competents pour la specialite \"%s\"\n" 
#define MSG_TRAVAILLEURS_TOUS "## consultation des travailleurs competents pour chaque specialite\n" 
#define MSG_CLIENT "## consultation des commandes effectuees par \"%s\"\n" 
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n" 
#define MSG_SUPERVISION "## consultation de l�avancement des commandes\n" 
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n" 
#define MSG_INTERRUPTION "## fin de programme\n" 

/////////////////////////////////////////////////
///	\brief Lexemes
/// 
/////////////////////////////////////////////////   
typedef enum { FAUX = 0, VRAI = 1 } Booleen;
Booleen EchoActif = FAUX;

#define LGMOT 35
#define NBCHIFFREMAX 5 
typedef char Mot[LGMOT + 1];

/////////////////////////////////////////////////
///	\brief Prototypes des fonctions
/// 
/////////////////////////////////////////////////
// Lexemes
void get_id(Mot id);
int get_int();

// Utilitaires

// Instructions
void traite_developpe();
void traite_embauche();
void traite_demarche();
void traite_progression();
void traite_passe();
void traite_commande();
void traite_tache();
void traite_specialites();
void traite_travailleurs();
void traite_client();
void traite_supervision();
void traite_charge();
void traite_interruption();

/////////////////////////////////////////////////
///	\brief Boucle principale
/// 
/// \param argc Nombre d'arguments
/// \param argv Arguments: "echo" permet un retour
/// � l'�cran de ce qu'on �crit via scanf
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

	Mot buffer;
	while (VRAI)
	{
		get_id(buffer);
		if (strcmp(buffer, "developpe") == 0)
		{
			traite_developpe();
			continue;
		}
		else if (strcmp(buffer, "embauche") == 0)
		{
			traite_embauche();
			continue;
		}
		else if (strcmp(buffer, "demarche") == 0)
		{
			traite_demarche();
			continue;
		}
		else if (strcmp(buffer, "commande") == 0)
		{
			traite_commande();
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
			traite_specialites();
			continue;
		}
		else if (strcmp(buffer, "travailleurs") == 0)
		{
			traite_travailleurs();
			continue;
		}
		else if (strcmp(buffer, "client") == 0)
		{
			traite_client();
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
///	\brief Traite l'instruction developpe
/// 
/// R�cup�re le nom de la sp�cialit� et son co�t
/// horraire
/// 
/// Affiche ensuite ces r�sultats
/// 
/////////////////////////////////////////////////  
void traite_developpe()
{
	Mot nom_specialite;

	get_id(nom_specialite);

	int cout_horaire = get_int();

	printf(MSG_DEVELOPPE, nom_specialite, cout_horaire);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction sp�cialit�s
/// 
/// Affiche la liste de tous les specialit�s 
/// existantes
/// 
/////////////////////////////////////////////////  
void traite_specialites()
{
	printf(MSG_SPECIALITES);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction travailleurs
/// 
/// R�cup�re la sp�cialit� pour lequel afficher
/// ses travailleurs, ou "tous" pour toutes les
/// sp�cialit�s
/// 
/// Affiche la liste de tous les travailleurs ou
/// d'une specialit� en particulier
/// 
///////////////////////////////////////////////// 
void traite_travailleurs()
{
	Mot nom_specialite;

	get_id(nom_specialite);

	if (strcmp(nom_specialite, "tous") == 0) // Pour toutes les sp�cialit�s
	{
		printf(MSG_TRAVAILLEURS_TOUS);
	}
	else
	{
		printf(MSG_TRAVAILLEURS, nom_specialite);
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction client
/// 
/// R�cup�re le nom du client pour lequel afficher
/// ses commandes, ou "tous" pour tous les
/// clients
/// 
/// Affiche la liste de toutes les commandes 
/// effectu�es par tous les clients ou pour un
/// client en particulier
/// 
///////////////////////////////////////////////// 
void traite_client()
{
	Mot nom_client;

	get_id(nom_client);

	if (strcmp(nom_client, "tous") == 0) // Pour tous les clients
	{
		printf(MSG_CLIENT_TOUS);
	}
	else
	{
		printf(MSG_CLIENT, nom_client);
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction supervision
/// 
/// Affiche la progression de toutes les 
/// commandes
/// 
///////////////////////////////////////////////// 
void traite_supervision()
{
	printf(MSG_SUPERVISION);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction charge
/// 
/// R�cup�re le nom du travailleur pour lequel on
/// veut afficher sa charge de travail
/// 
/// Affiche la charge de travail d'un travailleur
/// donn�
/// 
///////////////////////////////////////////////// 
void traite_charge()
{
	Mot nom_travailleur;

	get_id(nom_travailleur);

	printf(MSG_CHARGE, nom_travailleur);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction embauche
/// 
/// R�cup�re le nom de celui qui a �t� embauch� 
/// ainsi que la specialite dans laquelle il va exercer
/// 
/// Affiche son nom et sa sp�cialit�
/// 
///////////////////////////////////////////////// 
void traite_embauche()
{
	Mot nom_specialite, nom_embauch�;

	get_id(nom_embauch�);
	get_id(nom_specialite);

	printf(MSG_EMBAUCHER, nom_embauch�, nom_specialite);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction demarche
/// 
/// R�cup�re le nom du client entr�
/// 
/// Affiche le nom du client
/// 
///////////////////////////////////////////////// 
void traite_demarche()
{
	Mot nom_client;

	get_id(nom_client);

	printf(MSG_DEMARCHE, nom_client);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction commande
/// 
/// R�cup�re le nom de la commande et le client
/// 
/// Affiche le nom du client et le nom de la 
/// � effectuer
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
///	\brief Traite l'instruction tache
/// 
/// R�cup�re le nom de la commande, sa sp�cialit�
/// et le nombre d'heures pour effectuer la tache
/// 
/// Affiche la commande, la sp�cialit� associ�e
/// et le nombre d'heures n�cessaires pour 
/// effectuer la t�che de la sp�cialit�
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
///	\brief Traite l'instruction progression 
///
/// R�cup�re le nom de la commande, la sp�cialit�
/// et le nombre d'heures � ajouter � son 
/// avancement
/// 
/// Affiche le nombre d'heure r�alis�e pour une
/// sp�cialit� d'une commande en particulier
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
///	\brief Traite l'instruction passe
/// 
/// R�affecte la t�che
/// 
///////////////////////////////////////////////// 
void traite_passe()
{
	printf(MSG_PASSE);

}

/////////////////////////////////////////////////
///	\brief Traite l'instruction interruption
/// 
/// Met fin au programme
/// 
/////////////////////////////////////////////////  
void traite_interruption()
{
	printf(MSG_INTERRUPTION);
}

/////////////////////////////////////////////////
///	\brief R�cup�rer les entr�es de l'utilisateur
/// 
/// \param id Le mot entr�e
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
///	\brief R�cup�rer l'entr�e puis le convertir en
/// entier
/// 
/// \return L'entier r�cup�r�
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
