#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

typedef struct{
	float att;
	float def;
	float esq;
	int hp;
	char nom[50];
}Ninja;

Ninja constructeur_ninja(){
	Ninja n;
	printf("Choisir nom");
	scanf("%s", n.nom);
	n.att= (rand()%51)/10+5;
	n.def=(rand()%21)/10+2;
	n.esq=(rand()%11)/100+0.1;
	n.hp=(rand()%21)+80;
	return n;
}
void affiche_ninja(Ninja n){
	printf("Voici les stats de %s",n.nom);
	printf("attaque : %f\n défense : %f\n esquive : %f\n point de vie : %d\n", n.att, n.def, n.esq, n.hp);
}
	
	
	
	
	
	
	
void combat(Ninja a, Ninja b){
	esquive = (rand()%2)/10;
