#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "server.h"

Parametre *lire_param(char *param_fichier) {
    Parametre *param = (Parametre *) malloc(sizeof(Parametre));

    FILE *f = fopen(param_fichier, "r"); 
    fscanf(f, "%d", &(param->nombre)); 

    param -> victoire = (int *) malloc(sizeof(int) * param -> nombre); 
   
   
    param -> recomp = (int *) malloc(sizeof(int) * param -> nombre);

    for (int i = 0; i < param -> nombre; ++i)
        fscanf(f, "%d", &(param -> victoire[i]));

               for (int i = 0; i < param -> nombre; ++i)
                 param -> recomp[i] = 0;

                     for (int i = 0; i < param -> nombre; ++i)
     {
        int commun, recomp;
        fscanf(f, "%d %d", &commun, &recomp); 
        param -> recomp[commun - 1] += recomp;
    }

    return param;
}

bool handle_client(Parametre *param, int num[5], char ext[1024]) 
{
    int commun = 0, recompense = 0;

    for (int j = 0; j < param->nombre; ++j)
     { 
        for (int i = 0; i < 5; ++i)
     {
            if (num[i] == param->victoire[j]) 
     { 
                ++commun; 
                break;
            }
        }
    }

    recompense = param->recomp[commun - 1]; 

    int win = commun >= param->nombre;

    snprintf(ext, 1024, "%d %d %d", commun, recompense, win); 

    return win; 
}

int server(char *param_fichier) {
    Parametre *param = lire_param(param_fichier); 
    if (param == NULL) {
        printf("impossible de lire le fichier des numeros gagnants.\n");
        return -1;
    }

    char *fifoo = "million.sock";
    if (access(fifoo, F_OK) != -1) { 
        printf("un serveur est deja en cours d'execution.\n");
        return -1;
    }

    mkfifo(fifoo, 0666);
    int fichierr = open(fifoo, O_RDONLY); 
    if (!fichierr) {
        printf("impossible de lire le fichier.\n");
        return -1;
    }

    char dedans[1024], ext[1024];
    int pid, num[5];
    char fifo[32];
    int fichier;

    bool win = false;
    while (!win) { 
        if (read(fichierr, dedans, 1024) != 0) { 
            sscanf(dedans, "%d %d %d %d %d %d", &pid, &(num[0]), &(num[1]), &(num[2]), &(num[3]), &(num[4]));

            snprintf(fifo, 32, "million_%d.sock", pid);
            fichier = open(fifo, O_WRONLY); 
            if (!fichier) {
                printf("impossible de lire le fichier pour %d.\n", pid);
                continue;
            }

            win = handle_client(param, num, ext); 
            write(fichier, ext, strlen(ext) + 1);
            close(fichier);
        }
    }

   
   close(fichierr);
   
    remove(fifoo);

    free(param->victoire);
    
    free(param->recomp);
   
    free(param);
    return 0;
}
