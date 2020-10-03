#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "server.h"

Config *read_config(char *config_file) {
    Config *config = (Config *) malloc(sizeof(Config));

    FILE *f = fopen(config_file, "r"); // On ouvre le fichier de configuration
    fscanf(f, "%d", &(config->numbers)); // On lit le premier nombre

    config->winning = (int *) malloc(sizeof(int) * config->numbers); // On créé les deux tableaux qui stoquent les nombres gagnants et les récompenses
    config->rewards = (int *) malloc(sizeof(int) * config->numbers);

    for (int i = 0; i < config->numbers; ++i)
        fscanf(f, "%d", &(config->winning[i])); // On lit chaque nombre gagnant

    for (int i = 0; i < config->numbers; ++i)
        config->rewards[i] = 0; // On fait démarrer les récompenses à 0 au cas où

    for (int i = 0; i < config->numbers; ++i) {
        int matching, reward;
        fscanf(f, "%d %d", &matching, &reward); // On lit chaque récompense et on la stoque dans le tableau au bon endroit
        config->rewards[matching - 1] += reward;
    }

    return config;
}

bool handle_client(Config *config, int numbers[5], char out[1024]) {
    int matching = 0, reward = 0;

    for (int j = 0; j < config->numbers; ++j) { // Pour chaque nombre gagnant
        for (int i = 0; i < 5; ++i) {
            if (numbers[i] == config->winning[j]) { // On vérifie si le client l'a rentré
                ++matching; // Si oui, on le compte une seule fois
                break;
            }
        }
    }

    reward = config->rewards[matching - 1]; // On récupère sa récompense

    int won = matching >= config->numbers;

    snprintf(out, 1024, "%d %d %d", matching, reward, won); // On écrit dans la variable out le nombre de numéros gagnants, la récompense et s'il a gagné

    return won; // On renvoie 1 s'il a gagné, 0 sinon
}

int server(char *config_file) {
    Config *config = read_config(config_file); // On lit le fichier de config avec les numéros gagnants
    if (config == NULL) {
        printf("Unable to read config file.\n");
        return -1;
    }

    char *fifos = "million.sock";
    if (access(fifos, F_OK) != -1) { // Si le fichier million.sock existe déjà, c'est qu'il y a déjà un serveur qui tourne
        printf("A server is already running.\n");
        return -1;
    }

    mkfifo(fifos, 0666);
    int fds = open(fifos, O_RDONLY); // On ouvre le fichier million.sock pour écouter les requêtes des clients qui arrivent
    if (!fds) {
        printf("Unable to open file.\n");
        return -1;
    }

    char in[1024], out[1024];
    int pid, numbers[5];
    char fifoc[32];
    int fdc;

    bool won = false;
    while (!won) { // Tant qu'un client n'a pas gagné
        if (read(fds, in, 1024) != 0) { // On lit une requête d'un client
            sscanf(in, "%d %d %d %d %d %d", &pid, &(numbers[0]), &(numbers[1]), &(numbers[2]), &(numbers[3]), &(numbers[4]));

            snprintf(fifoc, 32, "million_%d.sock", pid);
            fdc = open(fifoc, O_WRONLY); // On ouvre le fichier correspond à ce client pour lui répondre
            if (!fdc) {
                printf("Unable to open client file for %d.\n", pid);
                continue;
            }

            won = handle_client(config, numbers, out); // On calcule le résultat de ses nombres
            write(fdc, out, strlen(out) + 1); // On répond au client
            close(fdc);
        }
    }

    // On supprime/ferme tous les fichiers et toutes les variables
    close(fds);
    remove(fifos);

    free(config->winning);
    free(config->rewards);
    free(config);
    return 0;
}
