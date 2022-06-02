#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxeleve 3
#define maxprof 5

FILE *globaluserfile;

 struct livre{
	char titre[30];
	char auteur[30];
	int id;
	char categorie[30];
	int  dateemprunt;
	char emprunteur[30];
};
struct user{
	char username[30];
	char mdp[30];
	int role; 
	int nblivres;
	int retard;
};
struct user globaluser;

int main(){
	FILE *infile;
	struct livre input1;
	char login[30];
	char mdp[30];
	int operation;
	infile = fopen("livre.dat", "r");
	globaluserfile = fopen("user.dat", "r");
	
	printf("\n ----liste des users----:\n");
	while(fread(&globaluser, sizeof(struct user), 1, globaluserfile))
	{
		printf (" username %s, nblivres %d , mdp %s, role %d, retard \n", globaluser.username, globaluser.nblivres,globaluser.mdp, globaluser.role, globaluser.retard);
    } 
	
	printf("\n ----liste des livres----:\n");
	infile = fopen ("livre.dat", "r");
	while(fread(&input1, sizeof(struct livre), 1, infile))
	{
		printf (" id = -%d- titre = -%s- emprunteur -%s- categorie -%s- auteur -%s- datemprunt %d \n", input1.id, input1.titre,input1.emprunteur, input1.categorie, input1.auteur, input1.dateemprunt);
    }   

	fclose (infile);
	fclose (globaluserfile);
}
