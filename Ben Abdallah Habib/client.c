#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "client.h"

int client(int numero[5]) {
    char *fifo = "million.sock";

    if (access(fifo, F_OK) == -1)
     { 
        printf("Aucun serveur ne tourne.\n");
        return 2;
    }

    int fichierr = open(fifo, O_WRONLY); 
    if (!fichierr) 
    {
        printf("Incapable d'ouvrir fichier serveur.\n");
        return -1;
    }

    int ident = getpid(); 
    char fifoo[32];
    snprintf(fifoo, 32, "million_%d.sock", ident);
    mkfifo(fifoo, 0666);

    int fichier = open(fifoo, O_RDWR); 
    if (!fichier) {
        printf("Incapable d'ouvrir le fichier client.\n");
        return -1;
    }
    
    
    char dedans[1024];
    
    
    do{}   
 while (read(fichier, dedans, 1024) == 0);
    close(fichier);
    remove(fifoo);

    char dehors[1024];
   
   
    snprintf(dehors, 1024, "%d %d %d %d %d %d", ident, numero[0], numero[1], numero[2], numero[3], numero[4]);
    write(fichierr, dehors, strlen(dehors) + 1);
    close(fichierr);



    int  recompense,commun, gagne;
    sscanf(dedans, "%d %d %d", &recompense, &commun, &gagne); 
    
     if (recompense > 0) {
        printf("Vous avez gagnés $%d!\n", recompense);
    } else {
        printf("Vous n'avez rien gagnés.\n");
    }
    
     if (gagne) {
        printf("Vous avez gagnés!\n");
        return 1;
    } else {
        return 0;
    }

    if (commun > 0) {
        printf("Vous avez trouvés %d numéros parmis les numéros gagnants .\n", commun);
    } else {
        printf("Vous n'avez trouvés aucun numéros correspondanrt au numéro gagnant.\n");
    }

   

   
}
