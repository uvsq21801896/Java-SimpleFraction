// NOM : BEN ABDALLAH
// Prénom : Habib
// Numéro étudiant : 21801896

#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Structure contenant une liste chaînée d'entiers
struct elem {
    int nb;
    struct elem *suivant;
};

void ecrire_fichier (struct elem *e, char *nom);

// Ajoute la valeur n à la liste chainée triée e. si n est déjà présent, on ne le rajoute pas.
// La liste modifiée ou pas est renvoyée
struct elem *inserer_trier (struct elem *e, int n)
{
    struct elem *element = e;
    struct elem new_element;

    new_element.nb = n;
    new_element.suivant = NULL;
    while (element->suivant != NULL)
        element = element->suivant;
    element->suivant = &new_element;
    return element;
}

// Renvoie une nouvelle liste chaînée contenant les entiers présents dans e1 ET dans e2.
// e1 et e2 ne doivent pas être modifiés
struct elem * intersection (struct elem *e1, struct elem *e2)
{
    struct elem *element1 = e1;
    struct elem *element2 = e2;
    struct elem *nouvelle_liste;

    while (element1->suivant != NULL){
        element2 = e2;
        if (element2->nb == element1->nb)
            inserer_trier(nouvelle_liste, element1->nb);
        while (element2->suivant != NULL)
            element2 = element2->suivant;
        element1 = element1->suivant;
    }
	return nouvelle_liste;
}

// Lit le fichier nom qui contient des entiers et les stocke de
// manière ordonnée dans une variable de type struct elem * qui est renvoyée
struct elem *lire_fichier (char *nom)
{
    char *buffer = NULL;
    struct elem *element;
    struct stat st;
    int size = 0;
    int fd = open(nom, O_RDONLY);

    stat(nom, &st);
    size = st.st_size;
    buffer = malloc(sizeof(char) * size + 1);
    buffer[size] = '\0';
    read(fd, buffer, size);
    close(fd);
    return element;
}


// Ecrit dans le fichier nom les entiers stockés dans la liste e.
//La fonction écrit un entier par ligne
void ecrire_fichier (struct elem *e, char *nom) 
{
    FILE *fichier = NULL;

    fichier = fopen(nom, "r+");
    fputc('\n', fichier);
    fclose(fichier);
}


// Le programme prend en argument trois noms de fichiers
// Le programme lit les deux premiers fichier et stocke pour chacun les entiers qu'ils contiennent dans une liste chaînée (une par fichier)
// Le programme calcule l'intersection des deux listes et écrit cet intersection dans le trosième fichier



int main(int argc, char *argv[])
{
    if (argc != 4)
        return 1;
    struct elem *fichier1 = lire_fichier(argv[1]);
    struct elem *fichier2 = lire_fichier(argv[2]);
    struct elem *intersect = intersection(fichier1, fichier2);
    //struct elem *intersect = intersection(fichier1, fichier2);
    //ecrire_fichier(intersect, argv[3]);
    return 0;
}
