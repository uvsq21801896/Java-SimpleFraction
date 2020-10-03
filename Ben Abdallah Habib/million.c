#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "server.h"

int main(int argc, char *argv[]) {
	if (argc > 1 && strcmp(argv[1], "server") == 0) { // Si le premier argument est "server"
		if (argc > 2) { // S'il y a un deuxième argument, qui représente le chemin vers le fichier de config
			return server(argv[2]); // On exécute le fichier server.c
		} else { // Sinon, on affiche qu'il manque le chemin vers ce fichier de config
			printf("Usage: ./million server <config_file>\n");
		}
	} else if (argc > 1 && strcmp(argv[1], "client") == 0) { // Si le premier argument est "client"
		if (argc > 6) { // S'il y a 5 arguments après, qui représentent les 5 nombres
			int numbers[5];
			for (int i = 0; i < 5; ++i)
				numbers[i] = atoi(argv[i + 2]); // On transforme les 5 arguments en 5 nombres et on les stoque dans un tableau

			return client(numbers); // On exécute le fichier client.c
		} else { // Sinon, on affiche qu'il manque les 5 nombres
			printf("Usage: ./million client <5 numbers>\n");
		}
	} else { // Sinon, on affiche que la sous-commande est incorrecte
		printf("Usage: ./million <server|client>\n");
		return -1;
	}
}
