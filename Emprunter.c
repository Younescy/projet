#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#define maxeleve 3
#define maxprof 5

FILE *globaluserfile;

 struct livre{
	char titre[30];
	char auteur[30];
	int id;
	char categorie[30];
	int signed long  dateemprunt;
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
unsigned long getTimeMicroSec(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return(1000000 * tv.tv_sec) +tv.tv_usec;
}
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
 
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
		clean_stdin();
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

int duree_s(time_t xtime)
{
    time_t now;
    time(&now);
    double seconds = difftime(now,xtime);
    return seconds;
}


int creat(){
    char login[30];
    int i; 
    int digit = 0;
    int upper = 0;
    int lower = 0;
    int letter = 0;
    int symbol = 0;
    int complexe = 0;
    FILE *outfile;
    outfile = fopen("user.dat", "a+");
    printf("Choisir votre pseudo:\n");
    lire(login, 30);
	printf("info : votre login : %s \n", login);
	// strcat(login, "\n");
    while(fread(&globaluser, sizeof(struct user), 1, outfile) && strcmp(globaluser.username,login))
    {
    }   
	
    if (strcmp(globaluser.username,login)==0){
	printf("ce login existe deja\n");
	exit(1);
	}
	globaluser.retard = 0;
	strcpy(globaluser.username, login);
	printf("Choisir votre role: \n 1-professeur \n 2-eleve\n");
	scanf("%d", &globaluser.role);
	if(globaluser.role!=1){
		if(globaluser.role!=2){
		printf("Veuillez saisir un role valide (1-professeur ou 2-eleve)\n");
		scanf("%d", &globaluser.role);
	}
	}
	printf("Choisir votre mot de passe:\n");
	while (complexe==0)	{
		lire( globaluser.mdp,30);
		for (i = 0; i < strlen(globaluser.mdp); i++) {
            if (isalpha(globaluser.mdp[i])) {
                letter++;
            }
            if (isupper(globaluser.mdp[i])) {
                upper++;
            }
            if (islower(globaluser.mdp[i])) {
                lower++;
            }
            if (isdigit(globaluser.mdp[i])) {
                digit++;
            }
            //Makes sure password has a symbol
            if (globaluser.mdp[i] == '!' || globaluser.mdp[i] == '@' || globaluser.mdp[i] == '#' || globaluser.mdp[i] == '$' || globaluser.mdp[i] == '%' || globaluser.mdp[i] == '^' || globaluser.mdp[i] == '&' || globaluser.mdp[i] == '*' || globaluser.mdp[i] == '(' || globaluser.mdp[i] == ')' || globaluser.mdp[i] == '-' || globaluser.mdp[i] == '+' || globaluser.mdp[i] == '_'){
				symbol++;
            }
        }
        if ( (strlen(globaluser.mdp)>8) && digit > 0 && upper > 0 && lower > 0 && letter > 0 && symbol > 0) {
		complexe=1;}
		else {
          printf ("Mot de passe incorrect, minimum 8 caracteres, une majuscule, une miuniscule et un symbole parmi !@#$%^*()-+_ \n");	
        }
    }

    printf("Enregistrement en cours...\n");
    fwrite (&globaluser, sizeof(struct user), 1, outfile);
    if(fwrite != 0){
        printf("\nDonnees enregistrees avec succces !\n");
	}
    else{
        printf("Erreur d ecriture des donnees  !\n");
	}
	 fclose(outfile);
}

int emprunter(){
	FILE *infile;
        struct livre input1;
	char title[30];
	int nbemprunts;
	time_t now;
	printf("info : Emprunt pour %s\n",globaluser.username);
    // open file for writing
    infile = fopen ("livre.dat", "r+");
    
	if (globaluser.retard > 0){
		printf("Vous n'avez plus le droit d'emprunter à cause de votre retard enregistre");
		exit(1);
	}
	
	if (infile == NULL)
    {   fprintf(stderr, "\nErreur ouverture du fichier \n");
        exit(1);
    }
	while(fread(&input1, sizeof(struct livre), 1, infile))
	{
		printf (" id = -%d- titre = -%s- emprunteur -%s- auteur -%s- categorie -%s-\n", input1.id, input1.titre,input1.emprunteur, input1.auteur, input1.categorie);
    }   
      
    // read struct to file
	
	printf("Donnez -svp- le titre du livre a emprunter :");
	fflush( stdout );
    	lire(title,30);
	printf("titre: %s\n",title);
	rewind(infile);

	while(fread(&input1, sizeof(struct livre), 1, infile) && strcmp(input1.titre,title)!=0)
	{
	}   
	
	if (strcmp(input1.titre,title)!=0){
		printf("Nous n'avons pas ce livre\n");
		exit(1);
	}
	if(strlen(input1.emprunteur)>1){
		printf("Livre deja emprunte");
		exit(1);
	}

	strcpy(input1.emprunteur, globaluser.username);
	time(&now);
	input1.dateemprunt=now;	
	printf("info - emprunteur: %s\n",  input1.emprunteur);
	printf("info - titre     : %s\n",  input1.titre);	
		
	fseek(infile, -sizeof(struct livre), SEEK_CUR);
	
	if(fwrite (&input1, sizeof(struct livre), 1, infile) != 0)
		 printf("Donnees enregistrees avec succces !\n");	 
    else
		 printf("Erreur d ecriture des donnees !\n");
	
	globaluser.nblivres ++;
	fseek(globaluserfile, -sizeof(struct user), SEEK_CUR);
	if(fwrite (&globaluser, sizeof(struct user), 1, globaluserfile) != 0)
		printf("Votre emprunt a ete enregistre \n" );
	else
        printf("\n Erreur de donnees  !\n");
	
	rewind (globaluserfile);
	while(fread(&globaluser, sizeof(struct user), 1, globaluserfile))
	{
    }  	
	fclose(globaluserfile);
    fclose (infile);
}

int restituer(){
	FILE *infile;
    struct livre input1;
	char title[30];
	int nbemprunts;
	time_t now;
    // open file for writing
    infile = fopen ("livre.dat", "r+");
	if (globaluser.nblivres==0){
		printf("Vous n'avez pas de livres a restituer !");
		exit(1);
	}
	printf("info : Restitution pour emprunteur %s\n",globaluser.username);
    if (infile == NULL)
    {
        fprintf(stderr, "\nErreur ouverture du fichier \n");
        exit(1);
    }
	while(fread(&input1, sizeof(struct livre), 1, infile))
	{
		printf (" id = -%d- titre = -%s- emprunteur -%s- auteur -%s-\n", input1.id, 	input1.titre,input1.emprunteur, input1.auteur);
    }   
      
    // read struct to file
	
	printf("Donnez -svp- le titre du livre a restituer :");
	fflush( stdout );
    	lire(title,30 );
	printf("titre: %s\n",title);
	rewind(infile);

	while(fread(&input1, sizeof(struct livre), 1, infile) && strcmp(input1.titre,title)!=0)
	{
	}   
	
	if (strcmp(input1.titre,title)!=0){
		printf("Nous n'avons pas ce livre");
		exit(1);
	}
	if(strcmp(input1.emprunteur, globaluser.username )!=0){
		printf("Vous n avez pas emprunte ce livre\n");
		exit(1);
	}

	strcpy(input1.emprunteur, "");
	input1.dateemprunt=time(NULL);
	printf("info - emprunteur: %s\n",  input1.emprunteur);
	printf("info - titre     : %s\n",  input1.titre);	

	
	fseek(infile, -sizeof(struct livre), SEEK_CUR);
	
	if(fwrite (&input1, sizeof(struct livre), 1, infile) != 0)
		 printf("Donnees enregistrees avec succces !\n");	 
    else
		 printf("Erreur d ecriture des donnees !\n");
	 
	time(&now);
	if ((duree_s(input1.dateemprunt) > 180 && globaluser.role==1) || (duree_s(input1.dateemprunt) > 120 && globaluser.role==2))
	{ printf("Vous avez depasse le temps autorise d'emprunt, vous serez interdit  d'emprunt dorenavant !\n");
	  globaluser.retard=1;
	}
    globaluser.nblivres --;
	fseek(globaluserfile, -sizeof(struct user), SEEK_CUR);
	if(fwrite (&globaluser, sizeof(struct user), 1, globaluserfile) != 0) {
		printf("Vous avez restitue %s\n",  input1.titre);
	}
	else{
        printf("\n Erreur de donnees  !\n");
	}
	 	
	fclose(globaluserfile);
    	fclose (infile);
	}

int ajoutlivre() {
	
	FILE *outfile;
	char title[30];
	char categorie[30];
	char auteur[30];
	int id=1;
	struct livre input1;
	outfile = fopen("livre.dat", "r");
	printf (" ----Ajouter livre ---");
	printf("Veuillez donner le titre:\n");
	lire( title,30);
	
	while(fread(&input1, sizeof(struct livre), 1, outfile))
	{
		if (strcmp(input1.titre,title)==0){
		printf("Ce livre existe deja");
		exit(1);
	}
	id++;
	}   
	
	printf("Veuillez donner la categorie:\n");
	lire( categorie,30);
	printf("Veuillez donner l'auteur:\n");
	lire( auteur,30);
	
	fclose(outfile);
	outfile = fopen ("livre.dat", "a+");*
	
	strcpy(input1.titre, title);
	strcpy(input1.categorie, categorie);
	strcpy(input1.auteur, auteur);
	strcpy(input1.emprunteur, "");
	input1.id=id;
	input1.dateemprunt=time(NULL);
		
	fwrite (&input1, sizeof(struct livre), 1, outfile);
	if(fwrite != 0)
        printf("Donnees enregistrees avec succces !\n");
    else
		 printf("Erreur d ecriture des donnees !\n");
	
}

int login(){
	FILE *infile;
	struct livre input2;
	char login[30];
	char mdp[30];
	int operation;
	infile = fopen("livre.dat", "r");
	globaluserfile = fopen("user.dat", "r+");
	printf("Donnez votre pseudo:\n");
	//clean_stdin();
	scanf("%s",login);
	while(fread(&globaluser, sizeof(struct user), 1, globaluserfile) && strcmp(globaluser.username,login)!=0)
	{
	}
	
	if (strcmp(globaluser.username,login)!=0){
		printf("ce login n'existe pas\n");
		exit(1);
	}
	printf("Donnez votre mot de passe:\n");
	//clean_stdin();
	scanf("%s",mdp);
	if(strcmp(globaluser.mdp, mdp)!=0){
		printf("Mot de passe errone\n");
		exit(1);
	}
	clean_stdin();
	while(fread(&input2, sizeof(struct livre), 1, infile))
	{
		if(strcmp(input2.emprunteur, login)==0){
			printf("Vous avez emprunte %s\n", input2.titre);
		}
    }   
	
	operation = 0;
	while(operation!=1 && operation!=2 && operation!=3 ){
		printf("Operation souhaitee: \n 1-emprunter \n 2-restituer\n");
		if(globaluser.role ==1) {
			printf(" 3-Ajouter un livre\n");
		}
		scanf("%d", &operation);
		if(operation!=1 && operation !=2 && operation !=3){
			printf("Action impossible!\n");
			exit(1);
}
		if(operation ==1){
			if((globaluser.role == 1 && globaluser.nblivres==maxprof ) || 		( globaluser.role == 2 && globaluser.nblivres==maxeleve )){
				printf("Vous ne pouvez pas emprunter car vous avez atteint 	votre quota\n Veuillez restituer un livre pour en emprunter un nouveau");
				printf("\nDeconnexion...");
				exit(1);
			}
			emprunter();
		}
		else if(operation ==2){
			restituer();
		}
		else if(operation == 3){
			 if( globaluser.role ==1) {
			ajoutlivre();
			 }
		}
		else{
			printf("Choix incorrect");
		}
	}
    
}

int main(){

	int choix;
	printf("Bienvenue, veuillez faire un choix\n");
	printf("1- Se connecter  \n2- Creer un compte\n");
	scanf("%d", &choix);
	if(choix==1){
		login();
	}
	else if(choix ==2){
		creat();
	}
	else{
		printf("Ce choix n est pas autorise");
		exit(1);
	}
	
	exit(1);
}


