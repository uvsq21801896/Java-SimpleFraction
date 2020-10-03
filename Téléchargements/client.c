#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"

int client(int numbers[5]) {
    char *fifos = "million.sock";

    if (access(fifos, F_OK) == -1) { // Si le fichier million.sock n'existe pas, c'est qu'il n'y a pas de serveur qui tourne
        printf("No server is running.\n");
        return 2;
    }

    int fds = open(fifos, O_WRONLY); // On ouvre le fichier million.sock pour écouter les requêtes des clients qui arrivent
    if (!fds) {
        printf("Unable to open server file.\n");
        return -1;
    }

    int pid = getpid(); // On récupère un identifiant unique pour cet identifiant
    char fifoc[32];
    snprintf(fifoc, 32, "million_%d.sock", pid);
    mkfifo(fifoc, 0666);

    int fdc = open(fifoc, O_RDWR); // On créé le fichier unique pour que le serveur réponde
    if (!fdc) {
        printf("Unable to open client file.\n");
        return -1;
    }

    char out[1024];
    snprintf(out, 1024, "%d %d %d %d %d %d", pid, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
    write(fds, out, strlen(out) + 1); // On envoie au serveur l'identifiant unique et les 5 numéros
    close(fds);

    char in[1024];
    while (read(fdc, in, 1024) == 0) {} // On attend la réponse du serveur
    close(fdc);
    remove(fifoc);

    int matching, reward, won;
    sscanf(in, "%d %d %d", &matching, &reward, &won); // On lit les 3 valeurs renvoyés par le serveur dans 3 variables

    if (matching > 0) {
        printf("You found %d matching numbers.\n", matching);
    } else {
        printf("You didn't find any matching numbers.\n");
    }

    if (reward > 0) {
        printf("You earned $%d!\n", reward);
    } else {
        printf("You didn't earn anything.\n");
    }

    if (won) {
        printf("You won!\n");
        return 1;
    } else {
        return 0;
    }
}
