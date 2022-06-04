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
int tri() {
	FILE *infile;
	FILE *outfile;
	char title[30];
	char lasttitle[30];
    long compt=1;
	long i=1;
	struct livre input1;
	struct livre output1;
	infile = fopen("livre.dat", "r");
	outfile = fopen("livretri.dat", "w");
	
    fread(&input1, sizeof(struct livre), 1, infile);
	strcpy(title,input1.titre);
	strcpy(output1.titre, input1.titre);
	strcpy(output1.categorie, input1.categorie);
	strcpy(output1.auteur, input1.auteur);
	strcpy(output1.emprunteur, input1.emprunteur);
	output1.id=input1.id;
	
	while(fread(&input1, sizeof(struct livre), 1, infile))	{
	compt++;
	if (strcmp(input1.titre,title) < 0) {
			strcpy(output1.titre, input1.titre);
			strcpy(output1.categorie, input1.categorie);
			strcpy(output1.auteur, input1.auteur);
			strcpy(output1.emprunteur, input1.emprunteur);
			output1.id=input1.id;
			output1.dateemprunt=input1.dateemprunt;
			strcpy(title,input1.titre);
	}
	};
	fwrite (&output1, sizeof(struct livre), 1, outfile);
	strcpy(lasttitle, title);
	compt--;
	while (i <= compt) {
		rewind(infile);
		strcpy(title,"zzzzzzzzz");
	    while(fread(&input1, sizeof(struct livre), 1, infile))	{
		if (strcmp(input1.titre,lasttitle) > 0) {
		 if (strcmp(input1.titre,title) <= 0) {
			strcpy(output1.titre, input1.titre);
			strcpy(output1.categorie, input1.categorie);
			strcpy(output1.auteur, input1.auteur);
			strcpy(output1.emprunteur,input1.emprunteur);
			output1.id=input1.id;
			output1.dateemprunt=input1.dateemprunt;
			strcpy(title,input1.titre);
	    }
		}
		}		
		fwrite (&output1, sizeof(struct livre), 1, outfile);
		strcpy(lasttitle, title);
		i++;		
	}
	fclose (outfile);
	fclose (infile);
}

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
	struct livre input5 = {"Animaux", "JK Rowling",5,"biologie",0,""};
	struct livre input6 = {"Etoiles", "JK Rowling",6,"astronomie",0,""};	
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
	tri();
	return 0;
}
