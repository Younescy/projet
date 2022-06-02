#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
 struct livre{
	char titre[30];
	char auteur[30];;
	int id;
	char categorie[30];;
	time_t  dateemprunt;
	char emprunteur[30];;
};

int main(){
	FILE *outfile;
    char title;
    // open file for writing
    outfile = fopen ("livre.dat", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }
 
    struct livre input1 = {"Divergente", "Younes",1,"action",0,""};
    struct livre input2 = {"PERCY-JACKSON", "dhoni",2,"action",0,""};
	struct livre input3 = {"Harry-Potter", "JK Rowling",3,"science fiction",0,""};
    struct livre input4 = {"Fruits", "JK Rowling",4,"botanique",0,""};
	struct livre input5 = {"Les animaux", "JK Rowling",5,"biologie",0,""};
	struct livre input6 = {"Les etoiles", "JK Rowling",6,"astronomie",0,""};	
    // write struct to file
    fwrite (&input1, sizeof(struct livre), 1, outfile);
    fwrite (&input2, sizeof(struct livre), 1, outfile);
	fwrite (&input3, sizeof(struct livre), 1, outfile);
	fwrite (&input4, sizeof(struct livre), 1, outfile);
	fwrite (&input5, sizeof(struct livre), 1, outfile);
	fwrite (&input6, sizeof(struct livre), 1, outfile);
	if(fwrite != 0)
        printf("Donnees enregistrees avec succces !\n");
    else
		 printf("Erreur d ecriture des donnees !\n");
	 
    // close file
    fclose (outfile);
	return 0;
}
