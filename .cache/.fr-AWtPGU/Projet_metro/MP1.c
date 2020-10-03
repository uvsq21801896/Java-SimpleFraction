#define TAILLE_MAX 60
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include"MP1.h"

/*---------------------CREATION D'UN TABLEAU QUI CONTIENDRA -------------------------*/
Station* creationListMetro(int taille)
{

    Station* listStation;
    listStation=(Station*)malloc(taille*sizeof(Station));
    return listStation;
}




/*----------------------------INITIALISATION DES ATTRIBUTS DE CHAQUE STATION--------------------*/
void initialisationStation(Station* listStation)
{
    int i;
    for(i=0;i<376;i++)
    {
        listStation[i].Arc1=-1;  //pour savoir si la station possède déjà une station voisine ou non
        listStation[i].Arc2=-1;  //pour savoir si la station possède une deuxieme station voisine ou est un terminus
        listStation[i].Arc3=-1;
        listStation[i].Arc4=-1;
        listStation[i].temps1=-1;
        listStation[i].temps2=-1;
        listStation[i].temps3=-1;
        listStation[i].temps4=-1;
        listStation[i].dejaVu=0;
        listStation[i].poids=-1;
        listStation[i].antecedent=-1;
        listStation[i].liste=-1;
        listStation[i].parent=-1;
        listStation[i].F=-1;
        listStation[i].G=-1;
        listStation[i].H=-1;





    }
}
/*
void  initialisationStationTerminus(int i,Station* listStation,int j)
{
        if(i!=-1)
        {

                int k=0;
                int temp;
                    if(listStation[i].Arc1==-1)
                        k++;
                        else
                    temp=listStation[i].Arc1;
                   if(listStation[i].Arc2==-1)
                        k++;
                        else
                    temp=listStation[i].Arc2;
                    if(listStation[i].Arc3==-1)
                        k++;
                        else
                    temp=listStation[i].Arc3;
                   if( listStation[i].Arc4=-1)
                        k++;
                        else
                    temp=listStation[i].Arc4;

                        if(k==3)
                        listStation[i].antecedent=temp;

        }
}*/


/*--------------------AFFICHAGE COMPLETE D'UNE STATION------------------------------*/


void verification(int i,Station* listStation)
{

    printf("\n\nnumeros : %d  Station : %sAbscisse : %d  Ordonnee : %d \narc1 : %d temps : %d \narc2 : %d temps : %d \narc3 : %d temps : %d \narc4 : %d temps : %d \ndeja vu : %d \npoids :%d \nantecedent : %d",
    listStation[i].NumerosSommet,listStation[i].Nom,listStation[i].Abscisse,listStation[i].ordonnees,listStation[i].Arc1,listStation[i].temps1,listStation[i].Arc2,
    listStation[i].temps2,listStation[i].Arc3,listStation[i].temps3,listStation[i].Arc4,listStation[i].temps4,listStation[i].dejaVu,listStation[i].poids,listStation[i].antecedent);

}
void verificationAstar(int i,Station* listStation)
{
    printf("\n\nnumeros : %d  Station : %sAbscisse : %d  Ordonnee : %d \narc1 : %d temps : %d \narc2 : %d temps : %d \narc3 : %d temps : %d \narc4 : %d temps : %d \nF : %d \n G : %d \n H :%d \nliste : %d \nparent :%d",
    listStation[i].NumerosSommet,listStation[i].Nom,listStation[i].Abscisse,listStation[i].ordonnees,listStation[i].Arc1,listStation[i].temps1,listStation[i].Arc2,
    listStation[i].temps2,listStation[i].Arc3,listStation[i].temps3,listStation[i].Arc4,listStation[i].temps4,listStation[i].F,listStation[i].G,listStation[i].H,listStation[i].liste,listStation[i].parent);

}




/*----------------------SAISIE DES INFORMATIONS DES STATIONS DE METRO------------------------------*/

void scanFichier(Station* listStation)
{

 FILE* fichier = NULL;
    char chaine[TAILLE_MAX];
    char chaine2[TAILLE_MAX]="";
    int numeros,numeros2;
    int i;
    int arc;
    int arcbis;
    int arc1;
    int arc2;
    int arc3;
    int arc4;
    int duree1;
    float duree;


    char nom[TAILLE_MAX];
    char nom2[TAILLE_MAX];

    fichier = fopen("metro.txt", "r");

    initialisationStation(listStation);


    if (fichier != NULL)
    {

            fgets(chaine, TAILLE_MAX, fichier); // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
            fgets(chaine, TAILLE_MAX, fichier);  //lit la deuxieme


     //on rentre dans le tableau les nom et numéros des stations


            for(i=0;i<376;i++)
            {
            fscanf(fichier,"%d",&listStation[i].NumerosSommet);
            fgets(listStation[i].Nom, TAILLE_MAX, fichier);
            }
                       // printf("%d %s",numeros,nom);  //affiche numéros 1 et nom 1
                        //printf("%d %s",numeros2,nom2); // On affiche la chaîne qu'on vient de lire

               // printf("%d %s",listStation[375].NumerosSommet,listStation[375].Nom);

            fgets(chaine, TAILLE_MAX, fichier); //passage d'une ligne inexploitable
            //printf("%s",chaine);

   //on rentre les coordonnés de chaque station :(abscisse et ordonnée)
            int temp;




            for(i=0;i<376;i++)
            {
            fscanf(fichier,"%d %d %d",&temp,&listStation[i].Abscisse,&listStation[i].ordonnees);

            }
                       // printf("%d %d",listStation[375].Abscisse,listStation[375].Ordonnees);

            fscanf(fichier,"%s %s",&chaine,&chaine2);




//remplissage des stations voisines avec les durees
            for(i=0;i<713;i++)
            {
            fscanf(fichier,"%d %d %d",&arc,&arc2,&duree1);

                     if(listStation[arc].Arc1==(-1))
                     {
                        listStation[arc].Arc1=arc2;
                        listStation[arc].temps1=duree1;
                     }
                     else
                     {
                        listStation[arc].Arc2=arc2;
                        listStation[arc].temps2=duree1;
                     }
            }
//vérification ok
        //    i=125;
          //  printf("%d %d %d %d %d",listStation[i].NumerosSommet,listStation[i].Arc1,listStation[i].Arc2,listStation[i].temps1,listStation[i].temps2);




 for(i=0;i<220;i++)
 {
        fscanf(fichier,"%d %d %f\n",&arcbis,&arc4,&duree);

            if(listStation[arcbis].Arc3==(-1))
            {
                listStation[arcbis].Arc3=arc4;
                listStation[arcbis].temps3=duree;   //on cast le float en int
            }
            else
            {
                listStation[arcbis].Arc4=arc4;
                listStation[arcbis].temps4=duree;
            }


 }

//vérification
          //  i=367;
         // printf("%d %d %d %d %d",listStation[i].NumerosSommet,listStation[i].Arc3,listStation[i].Arc4,listStation[i].temps3,listStation[i].temps4);
/*int i;
for(i=0;i<376;i++)
{
    initialisationStationTerminus(listStation[i].Arc1,listStation,i);
    initialisationStationTerminus(listStation[i].Arc2,listStation,i);
    initialisationStationTerminus(listStation[i].Arc3,listStation,i);
    initialisationStationTerminus(listStation[i].Arc4,listStation,i);
}*/
fclose(fichier);





}
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier");
    }
fclose(fichier);

}

/*---------------------------------ALGORITHME DE DIJKSTRA-----------------------------------------*/

void dijkstra(int numerosDepart,int numerosArrivee,Station* listStation)
{
int StationMini=-1;
int k=0;
    listStation[numerosDepart].poids=0;   //on initialise la statiion de départ à 0

while((StationMini!=numerosArrivee)&&(k<100))
{
    //printf("%s",listStation[numerosArrivee].Nom);
  StationMini=minimumPoids(listStation,numerosArrivee); //on chercher la station ayant le poids le plus faible

 if(StationMini==-1)
    {
        printf("minimum pas trouve, %d operatios faites\n",k);
    }
   if(listStation[StationMini].Arc1!=-1)  //on liste tous les voisins et on recalcule leur nouveau poids
       calculPoids(StationMini,listStation[StationMini].Arc1,listStation[StationMini].temps1, listStation);
    if(listStation[StationMini].Arc2!=-1)
        calculPoids(StationMini,listStation[StationMini].Arc2,listStation[StationMini].temps2,listStation);
     if(listStation[StationMini].Arc3!=-1)
        calculPoids(StationMini,listStation[StationMini].Arc3,listStation[StationMini].temps3, listStation);
    if(listStation[StationMini].Arc4!=-1)
        calculPoids(StationMini,listStation[StationMini].Arc4,listStation[StationMini].temps4, listStation);


k++;
listStation[StationMini].dejaVu=1;

}
AfficheResultat(numerosDepart,numerosArrivee,listStation);


}

int minimumPoids(Station* listStation,int numerosArrivee)
{
    int i;
    int temp=1000;
    int numerosMin=-1;
    for(i=0;i<376;i++)
    {
        if(listStation[i].poids<=temp)
            if(listStation[i].dejaVu==0)
                if(listStation[i].poids!=-1)
            {
            numerosMin=i;
            temp=listStation[i].poids;
            }
    }
    return numerosMin;
}

void calculPoids (int numerosSommetDepart,int numerosSommetArrivee,int distance,Station* listStation)
{

    if(listStation[numerosSommetDepart].dejaVu==0)
    {
        if(listStation[numerosSommetArrivee].poids>=(listStation[numerosSommetDepart].poids+distance))
        {
            listStation[numerosSommetArrivee].poids=listStation[numerosSommetDepart].poids+distance;
            listStation[numerosSommetArrivee].antecedent=numerosSommetDepart;
            //if(numerosSommetArrivee==166)
           // printf("antecedent a %d",numerosSommetArrivee);
        }
        if(listStation[numerosSommetArrivee].poids==-1)
         {
            listStation[numerosSommetArrivee].poids=listStation[numerosSommetDepart].poids+distance;
            listStation[numerosSommetArrivee].antecedent=numerosSommetDepart;
           // if(numerosSommetArrivee==166)
            //printf("antecedent a %d",numerosSommetArrivee);
        }



//printf("deja vu : %d\n",numerosSommetDepart);


    }
}


/*-----------------------------AFFICHAGE DES STATIONS------------------------------------*/


void AfficheResultat(int numerosDepart,int numerosArrivee,Station* listStation)
{
    printf("-----------------------ALGORITHME DE DIJKSTRA-------------------\n");
    int i=1;
    int temp=numerosArrivee;
    while(temp!=-1)
    {
    printf("Etape %d : %s \n",i,listStation[temp].Nom);
    temp=listStation[temp].antecedent;
    i++;
    if(i==100)
    break;
    }
}

/*---------------------------------ALGORITHME A*  ------------------------------------------*/


void A(int numerosDepart,int numerosArrivee,Station* listStation)
{
int caseActuelle;
    int k=0;
    listStation[numerosDepart].liste=0;   //on ajoute a la liste ouverte

while((caseActuelle!=numerosArrivee)&&(k<1000))
{
    caseActuelle=calculMinimum(listStation);
    if(caseActuelle==-1)
    {
        printf("minimum pas trouve, %d operatios faites\n",k);
    break;
    }
    listStation[caseActuelle].liste=1;  //on cherche le noeud ac le poids le plus petit et on l'ajoute a la liste ouverte

    if(listStation[caseActuelle].Arc1!=-1)
            calculAstar(listStation[caseActuelle].Arc1,caseActuelle,listStation[caseActuelle].temps1,listStation);
    if(listStation[caseActuelle].Arc2!=-1)
            calculAstar(listStation[caseActuelle].Arc2,caseActuelle,listStation[caseActuelle].temps2,listStation);
    if(listStation[caseActuelle].Arc3!=-1)
            calculAstar(listStation[caseActuelle].Arc3,caseActuelle,listStation[caseActuelle].temps3,listStation);
    if(listStation[caseActuelle].Arc4!=-1)
            calculAstar(listStation[caseActuelle].Arc4,caseActuelle,listStation[caseActuelle].temps4,listStation);


k++;
}
AfficheResultatA(numerosDepart,numerosArrivee,listStation);
printf("parent depart : %d\n",listStation[numerosDepart].parent);
printf("parent arrivee : %d\n",listStation[numerosArrivee].parent);
}


void calculAstar(int caseAdjacente,int caseActuelle,int G, Station* listStation)
{

        listStation[caseAdjacente].liste=0;   // on l'ajoute ds la liste ouverte

       if(listStation[caseAdjacente].F=-1)  /*Si on a jamais observé ce noeud*/
       {
        listStation[caseAdjacente].G=G;
        listStation[caseAdjacente].H=
        distance(listStation[caseAdjacente].Abscisse,listStation[caseAdjacente].ordonnees,
        listStation[caseActuelle].Abscisse,listStation[caseActuelle].ordonnees);
        listStation[caseAdjacente].F=(listStation[caseAdjacente].G)+(listStation[caseAdjacente].H);
        listStation[caseAdjacente].parent=caseActuelle;
       }
       else  /*on regarde si on peut améliorer le résultat*/
       if(listStation[caseAdjacente].F>(G+   (distance(listStation[caseAdjacente].Abscisse,listStation[caseAdjacente].ordonnees,
    listStation[caseActuelle].Abscisse,listStation[caseActuelle].ordonnees))))
    {
        listStation[caseAdjacente].G=G;
        listStation[caseAdjacente].H=
        distance(listStation[caseAdjacente].Abscisse,listStation[caseAdjacente].ordonnees,
        listStation[caseActuelle].Abscisse,listStation[caseActuelle].ordonnees);
        listStation[caseAdjacente].F=(listStation[caseAdjacente].G)+(listStation[caseAdjacente].H);
        listStation[caseAdjacente].parent=caseActuelle;
    }


}
int calculMinimum(Station* listStation)
{
    int min=1000,i;
    int StationMini=-1;
    for(i=0;i<376;i++)
    {
        if(listStation[i].liste==0)
                if(listStation[i].F<min)
                    {
                    min=listStation[i].F;
                    StationMini=i;
                    }

    }

return StationMini;
}
/* calcule la distance entre les points (x1,y1) et (x2,y2) */
int distance(int x1, int y1, int x2, int y2)
{
    /* distance euclidienne */
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

}


/*------------------AFFICHAGE RESULTAT A STAR-------------------------*/


void AfficheResultatA(int numerosDepart,int numerosArrivee,Station* listStation)
{
    printf("----------------ALGORITHME A*----------------------\n");
    int i=1;
    int temp=numerosArrivee;
    while(temp!=-1)
    {
    printf("Etape %d : %s \n",i,listStation[temp].Nom);
    temp=listStation[temp].parent;
    i++;
    if(i==100)
    break;
    }
}



