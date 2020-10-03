#define TAILLE_MAX 60
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "MP1.h"

int main(int argc, char *argv[])
{

    Station* listMetro;
    listMetro=creationListMetro(376);
    scanFichier(listMetro);
    printf("entrer le numeros de depart");

   int numerosDepart,numerosArrivee;
  // numerosDepart=139;
   //numerosArrivee=55;
/*----------------------erreur   130->66;-------------*/
/*--------------------erreur 37->251,342--------------------------*/

   scanf("%d",&numerosDepart);
   printf("entrer le numeros d'arrivee");
   scanf("%d",&numerosArrivee);

   dijkstra(numerosArrivee,numerosDepart,listMetro);
    //A(numerosArrivee,numerosDepart,listMetro);
    /*------------problème----------*/
    //verificationAstar(150,listMetro);
    //verification(166,listMetro);
    //verification(119,listMetro);
    //verification(16,listMetro);
    //verification(130,listMetro);
    //verification(67,listMetro);
    //verification(80,listMetro);
    //verification(166,listMetro);









    return 0;
}


