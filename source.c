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
#define MSG_SPECIALITES "## consultation des specialites\n" 
#define MSG_TRAVAILLEURS "## consultation des travailleurs competents pour la specialite \"%s\"\n" 
#define MSG_TRAVAILLEURS_TOUS "## consultation des travailleurs competents pour chaque specialite\n" 
#define MSG_CLIENT "## consultation des commandes effectuees par \"%s\"\n" 
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n" 
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n" 
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
void traite_interruption();
void traite_specialites();
void traite_travailleurs();
void traite_client();
void traite_supervision();
void traite_charge();

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
	if(argc >= 2 && strcmp("echo", argv[1]) == 0) 
	{
		EchoActif = VRAI;
	}

	Mot buffer;
	while(VRAI)
	{
		get_id(buffer);
		if(strcmp(buffer, "developpe") == 0)
		{
			traite_developpe();
			continue;
		}
		else if(strcmp(buffer, "specialites") == 0)
		{
			traite_specialites();
			continue;
		}
		else if(strcmp(buffer, "travailleurs") == 0)
		{
			traite_travailleurs();
			continue;
		}
		else if(strcmp(buffer, "client") == 0)
		{
			traite_client();
			continue;
		}
		else if(strcmp(buffer, "supervision") == 0)
		{
			traite_supervision();
			continue;
		}
		else if(strcmp(buffer, "charge") == 0)
		{
			traite_charge();
			continue;
		}
		else if(strcmp(buffer, "interruption") == 0)
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
	
	if(strcmp(nom_specialite, "tous") == 0) // Pour toutes les sp�cialit�s
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
///	\brief R�cup�rer les entr�es de l'utilisateur
/// 
/// \param id Le mot entr�e
/// 
/////////////////////////////////////////////////   
void get_id(Mot id)
{
	scanf("%s", id);

	if(EchoActif)
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

	if(EchoActif)
	{
		printf(">>echo %s\n", buffer);
	}

	return atoi(buffer);
}