#include"../include/config.h"

void initFromConfig(char** config) {

	FILE *fp;
	char line[MAX_CONFIG_LINE];
	char *word;
	int i;

	if ((fp = fopen("../config/config.ini", "r")) == NULL) {
		perror("Error in fopen()");
		exit(-1);
	}

	while(fgets(line, MAX_CONFIG_LINE, fp)){
		for ( i = 0; i < MAX_CONFIG_LINE; i++) {
			if (line[i] != ' ' || line[i] != '\t') {
				break;
			}
		}

		if (line[0] == '#' || line[0] == '\n') {
			continue;
		}

		word = strtok(line, "=");

		if (strcmp(word, "THREADS") == 0) {
			word = strtok(NULL, "\n");
			config[THREADS] = strdup(word);
			continue;
		}

		if (strcmp(word, "PORT") == 0) {
			word = strtok(NULL, "\n");
			config[PORT] = strdup(word);
			continue;
		}

		if (strcmp(word, "PATH") == 0) {
			word = strtok(NULL, "\n");
			config[PATH] = strdup(word);
			continue;
		}
	}

}

