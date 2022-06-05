#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define maxeleve 3
#define maxprof 5

FILE *globaluserfile;
unsigned long debut;
unsigned long fin;

 struct livre{
	char titre[30];
	char auteur[30];
	int id;
	char categorie[30];
	time_t  dateemprunt;
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

unsigned long duree_s(time_t xtime)
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
	tri();
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
		lire(globaluser.mdp, 30);
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
            if (globaluser.mdp[i] == '!' || globaluser.mdp[i] == '@' || globaluser.mdp[i] == '#' || globaluser.mdp[i] == '$' || globaluser.mdp[i] == '%' || globaluser.mdp[i] == '&' || globaluser.mdp[i] == '*' || globaluser.mdp[i] == '(' || globaluser.mdp[i] == ')' || globaluser.mdp[i] == '-' || globaluser.mdp[i] == '+' || globaluser.mdp[i] == '_'){
				symbol++;
            }
        }
        if ( (strlen(globaluser.mdp)>8) && digit > 0 && upper > 0 && lower > 0 && letter > 0 && symbol > 0) {
		complexe=1;}
		else {
          printf ("Mot de passe incorrect, minimum 8 caracteres, une majuscule, une miniscule et un symbole parmi !@#$%*()-+_ \n");	
        }
    }

    printf("Enregistrement en cours...\n");
    fwrite (&globaluser, sizeof(struct user), 1, outfile);
    if(fwrite !=0){
        printf("\nDonnees enregistrees avec succces !\n");
	}
    else{
        printf("Erreur d ecriture des donnees  !\n");
	}
	 fclose(outfile);
	 return;
}

void emprunter(){
	FILE *infile;
	FILE *infiletri;
    struct livre input1;
	char title[30];
	char tmp[30];
	time_t my_time;
	printf("info : Emprunt pour %s\n",globaluser.username);
    // open file for writing
	tri();
    infile = fopen ("livre.dat", "r+");
    
	if (globaluser.retard > 0){
		printf("Vous n'avez plus le droit d'emprunter à cause de votre retard enregistre\n");
		exit(1);
	}
	
	infile = fopen ("livre.dat", "r+");	
	if (infile == NULL)
    {   fprintf(stderr, "\nErreur ouverture du fichier livre \n");
        exit(1);
    }
	printf("\n ----liste des livres----:\n");
	while(fread(&input1, sizeof(struct livre), 1, infile))
	{
		printf (" id = -%d- titre = -%s- emprunteur -%s- categorie -%s- auteur -%s- datemprunt %d \n",input1.id, input1.titre,  input1.emprunteur, input1.categorie, input1.auteur, input1.dateemprunt);
    }   
    
	infiletri = fopen ("livretri.dat", "r");
    if (infiletri == NULL)
    {
        fprintf(stderr, "\nErreur ouverture du fichier livre tri \n");
        exit(1);
    }
	printf("\n ----liste des livres TRIES par Titre----:\n");
	while(fread(&input1, sizeof(struct livre), 1, infiletri))
	{
		printf (" id = -%d- titre = -%s- emprunteur -%s- categorie -%s- auteur -%s- datemprunt %d \n",input1.id, input1.titre,  input1.emprunteur, input1.categorie, input1.auteur, input1.dateemprunt);
    }   
    fclose (infiletri);  
	 
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
		printf("Livre deja emprunte \n");
		exit(1);
	}

	strcpy(input1.emprunteur, globaluser.username);
	printf("info - emprunteur: %s\n",  input1.emprunteur);
	printf("info - titre     : %s\n",  input1.titre);	
	time(&my_time);
	input1.dateemprunt = my_time;
		
	fseek(infile, -sizeof(struct livre), SEEK_CUR);
	
	if(fwrite (&input1, sizeof(struct livre), 1, infile) != 0)
		 printf("Donnees enregistrees avec succces !\n");	 
    else
		 printf("Erreur d ecriture des donnees !\n");
	fclose (infile);
	tri();
	
	globaluser.nblivres ++;
	fseek(globaluserfile, -sizeof(struct user), SEEK_CUR);
	if(fwrite (&globaluser, sizeof(struct user), 1, globaluserfile) != 0)
		printf("Votre emprunt a ete enregistre \n" );
	else
        printf("\n Erreur de donnees  !\n");

	return;
}

int restituer(){
	FILE *infile;
	FILE *infiletri;
    struct livre input1;
	char title[30];
	int duree;
	time_t emprunt_time;
    // open file for writing
	tri();
   
	if (globaluser.nblivres==0){
		printf("Vous n'avez pas de livres a restituer !");
		exit(1);
	}
	printf("info : Restitution pour emprunteur %s\n",globaluser.username);
	infiletri = fopen ("livretri.dat", "r");
    if (infiletri == NULL)
    {
        fprintf(stderr, "\nErreur ouverture du fichier livre tri \n");
        exit(1);
    }
	printf("\n --Liste des livres empruntes par >>> %s :\n", globaluser.username);
	while(fread(&input1, sizeof(struct livre), 1, infiletri))
	{
		if(strcmp(input1.emprunteur, globaluser.username )==0) {
		printf ("- id = -%d- titre = -%s emprunteur -%s- categorie -%s- auteur -%s- datemprunt %d \n", input1.id,  input1.titre, input1.emprunteur, input1.categorie, input1.auteur, input1.dateemprunt);
		}   
	}
    fclose (infiletri);  
	
	infile = fopen ("livre.dat", "r+");  
	if (infile == NULL)
    {
        fprintf(stderr, "\nErreur ouverture du fichier des livres \n");
        exit(1);
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
	printf("info - emprunteur: %s\n",  globaluser.username);
	printf("info - titre     : %s\n",  input1.titre);	
	
	if(strcmp(input1.emprunteur, globaluser.username )!=0){
		printf("Vous n avez pas emprunte ce livre\n");
		exit(1);
	}

	fseek(infile, -sizeof(struct livre), SEEK_CUR);
	
	if(fwrite (&input1, sizeof(struct livre), 1, infile) != 0)
		 printf("Donnees restitution enregistrees avec succces !\n");	 
    else
		 printf("Erreur d ecriture des donnees !\n");
	fclose (infile);
	tri();
	emprunt_time=input1.dateemprunt;
	duree = duree_s(input1.dateemprunt);
	printf("duree emprunt en secondes duree_s : %d \n",  duree);

	if (((duree > 180) && (globaluser.role==1)) || ((duree > 120) && (globaluser.role==2)))
	{ printf("Vous avez depasse le temps autorise d'emprunt, vous serez interdit d emprunt dorenavant !\n");
	  globaluser.retard=1;
	}
    globaluser.nblivres --;
	strcpy(input1.emprunteur, "");
	input1.dateemprunt=0;
	fseek(globaluserfile, -sizeof(struct user), SEEK_CUR);
	if(fwrite (&globaluser, sizeof(struct user), 1, globaluserfile) != 0) {
		printf("Vous avez restitue %s\n",  input1.titre);
	}
	else{
        printf("\n Erreur de donnees  !\n");
	}
	 	
	return;

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
	if(fwrite != 0) {
        printf("Donnees enregistrees avec succces !\n");
	    tri();
	}
    else
	{
		 printf("Erreur d ecriture des donnees !\n");
	}
	fclose (outfile);
	tri();
	return;
}

void tri() {
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
	
    while (action() !=9);
	
   return; 
}


int action(){
	int operation;
	operation = 0;
	while(operation!=1 && operation!=2 && operation!=3 ){
		printf("Operation souhaitee: \n 1-emprunter \n 2-restituer\n");
		if(globaluser.role ==1) {
			printf(" 3-Ajouter un livre\n");
		}
		printf(" 9-Quitter\n");
		scanf("%d", &operation);
		if(operation!=1 && operation !=2 && operation !=3 && operation !=9){
			printf("Choix incorrect!\n");
		}
		if(operation==9){
			printf("Deconnexion...");
			exit(1);
		}
			

		if(operation ==1){
			if((globaluser.role == 1 && globaluser.nblivres==maxprof ) || ( globaluser.role == 2 && globaluser.nblivres==maxeleve )){
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
		};
		
	}
   return operation; 
}

int main(){

	int choix;
	printf("------------Bibliotheque CY tech-------------\n");
	printf("Bienvenue, veuillez faire un choix\n");
	printf("1- Se connecter  \n2- Creer un compte\n3- Quitter la bibliotheque\n");
	scanf("%d", &choix);
	if(choix==1){
		login();
	}
	else if(choix ==2){
		creat();
	}
	else if(choix==3){
		exit(1);
	}
	else{
		printf("Ce choix n est pas autorise\n");
		exit(1);
	}
   fclose(globaluserfile);
	exit(1);
}


