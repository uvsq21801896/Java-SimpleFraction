#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	setbuf(stdout, NULL);

	if (argc < 2) {
		printf("Utilisez : ./main info.txt\n");
		return 1;
	}

	int info[5];

	FILE *f = fopen(argv[1], "r");
	for (int i = 0; i < 5; ++i)
		fscanf(f, "%d", &info[i]);
	fclose(f);

	int **pipes = (int **) malloc(sizeof(int *) * info[3]);

	for (int i = 0; i < info[3]; ++i) {
		pipes[i] = (int *) malloc(sizeof(int) * 4);
		pipe(&pipes[i][0]);
		pipe(&pipes[i][2]);

		int flag = fcntl(pipes[i][0], F_GETFL, 0);
		fcntl(pipes[i][0], F_SETFL, flag | O_NONBLOCK);
	}

	int i, pid = 0;
	for (i = 0; i < info[3] && pid == 0; ++i)
		pid = fork();

	if (pid < 0) {
		printf("Erreur lors de la création des processus fils.\n");
		return 2;
	}

	if (pid == 0) {
		int logique_lru[info[0]];
		int physique_lru[info[0]];
		for (int i = 0; i < info[0]; ++i) {
			logique_lru[i] = i;
			physique_lru[i] = -1;
		}

		int hits[info[3]];
		int access[info[3]];
		for (int i = 0; i < info[3]; ++i) {
			hits[i] = 0;
			access[i] = 0;
		}

		while (1) {
			int running = 0;

			for (int i = 0; i < info[3]; ++i) {
				if (access[i] < info[4]) {
					running = 1;
					break;
				}
			}

			if (!running) {
				break;
			}

			for (int i = 0; i < info[3]; ++i) {
				char string_in[1024];
				if (read(pipes[i][0], string_in, 1024) <= 0) continue;

				int adresse_physique = atoi(string_in);
				++access[i];

				int j;
				for (j = 0; j < info[0]; ++j) {
					if (physique_lru[j] == adresse_physique) {
						++hits[i];
						break;
					}
				}

				if (j == info[0])
					--j;
				int adresse_logique = logique_lru[j];

				for (int k = j; k > 0; --k) {
					logique_lru[k] = logique_lru[k - 1];
					physique_lru[k] = physique_lru[k - 1];
				}

				logique_lru[0] = adresse_logique;
				physique_lru[0] = adresse_physique;

				char string_out[1024];
				sprintf(string_out, "%d", adresse_logique);
				write(pipes[i][3], string_out, 1024);
			}
		}

		wait(NULL);

		printf("Statistiques :\n");
		for (int i = 0; i < info[3]; ++i)
			printf("%2d = %d hits\n", i + 1, hits[i]);
	} else {
		--i;
		srand(time(NULL) ^ (getpid() << 16));

		for (int j = 0; j < info[4]; ++j) {
			int adresse_physique = rand() % (info[1] / info[2]);

			// Fait en sorte que les adresses "basses" sont plus souvent appelées que les adresses "hautes"
			// Cela ressemble plus à une utilisation de la mémoire proche de la réalité
			// Comme ça, les accès ne sont pas purement aléatoires et le cache LRU est plus efficace
			adresse_physique = adresse_physique * adresse_physique / (info[1] / info[2]);

			char string_out[1024];
			sprintf(string_out, "%d", adresse_physique);
			write(pipes[i][1], string_out, 1024);

			char string_in[1024];
			if (read(pipes[i][2], string_in, 1024) <= 0) continue;

			int adresse_logique = atoi(string_in);

			printf("%2d = %d\n", adresse_physique, adresse_logique);
		}

		exit(0);
	}

	return 0;
}
