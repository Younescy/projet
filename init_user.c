#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a struct to read and write
struct user{
	char username[30];
	char mdp[30];
	int role;
	int nblivres;
	int retard;
};
 
int main ()
{
    FILE *outfile;
	FILE *infile;
    // open file for writing
    outfile = fopen ("user.dat", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }
 
    struct user input1 = {"Younes", "Younes1234@",2,0,0};
    struct user input2 = {"Professeur", "Professeur1234@",1,0,0};
    struct user input3 = {"Eleve", "Eleve1234@",2,0,0};
     
    // write struct to file
    fwrite (&input1, sizeof(struct user), 1, outfile);
    fwrite (&input2, sizeof(struct user), 1, outfile);
    fwrite (&input3, sizeof(struct user), 1, outfile);
    
    if(fwrite != 0)
        printf("Donnees enregistrees avec succces !\n");
    else
        printf("Erreur d ecriture des donnees  !\n");
	fclose(outfile);
	infile = fopen("user.dat" ,"r");
	while(fread(&input3, sizeof(struct user), 1, infile))
	{
		printf (" username %s, mdp %s, role %d, nblivres %d, retard %d \n", input3.username, input3.mdp,input3.role, input3.nblivres, input3.retard);
    } 
    // close file
    fclose (infile);
    return 0;
}
