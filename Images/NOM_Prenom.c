// NOM :
// Prénom :
// Numéro étudiant : 

#include "stdio.h"
#include "stdlib.h"

// Structure contenant une liste chaînée d'entiers
struct elem {

};

// Ajoute la valeur n à la liste chainée triée e. si n est déjà présent, on ne le rajoute pas.
// La liste modifiée ou pas est renvoyée
struct elem * inserer_trier (struct elem *e, int n)
{
	return NULL;
}

// Renvoie une nouvelle liste chaînée contenant les entiers présents dans e1 ET dans e2.
// e1 et e2 ne doivent pas être modifiés
struct elem * intersection (struct elem *e1, struct elem *e2)
{
	return NULL;
}

// Lit le fichier nom qui contient des entiers et les stocke de
// manière ordonnée dans une variable de type struct elem * qui est renvoyée
struct elem * lire_fichier (char *nom)
{
	return NULL;
}


// Ecrit dans le fichier nom les entiers stockés dans la liste e.
//La fonction écrit un entier par ligne
void ecrire_fichier (struct elem *e, char *nom) 
{

}


// Le programme prend en argument trois noms de fichiers
// Le programme lit les deux premiers fichier et stocke pour chacun les entiers qu'ils contiennent dans une liste chaînée (une par fichier)
// Le programme calcule l'intersection des deux listes et écrit cet intersection dans le trosième fichier

int main(int argc, char *argv[])
{
	return 0;
}
