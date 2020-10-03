#include <stdlib.h>
#include <stdio.h>


int main(){
	printf("Quel numéro souhaitez-vous soumettre ? \n");

int nombre_aleatoire1,nombre_aleatoire2,nombre_aleatoire3,nombre_aleatoire4,nombre_aleatoire5;

nombre_aleatoire1=8;
nombre_aleatoire2=7;
nombre_aleatoire3=9;
nombre_aleatoire4=67;
nombre_aleatoire5=87;

 printf("j'envoie %d %d %d %d %d au serveur !\n",nombre_aleatoire1, nombre_aleatoire2, nombre_aleatoire3, nombre_aleatoire4, nombre_aleatoire5);
 
 int alea1=rand()%99;
	int alea2=rand()%99;
	int alea3=rand()%99;
	int alea4=rand()%99;
	int alea5=rand()%99;
	printf("les chiffres sont %d %d %d %d %d. \n",alea1,alea2,alea3,alea4,alea5);
	
	if(nombre_aleatoire1==alea1 && nombre_aleatoire2==alea2 && nombre_aleatoire3==alea3 && nombre_aleatoire4==alea4 && nombre_aleatoire5==alea5){
	printf("C'est gagné !");
}	
    
    else {
	printf("C'est perdu !");
}	
	
}
