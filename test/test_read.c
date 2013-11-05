#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _GNU_SOURCE

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("Please input your word_list filepath.\n");
		exit(0);
	}
	const char* filepath = argv[1];
	FILE* fp = NULL;
	fp = fopen(filepath, "r");
	if (NULL == fp) {
		printf("[ERROR] -- can not open filepath: %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	char* line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		printf("%s", line);
	}
	free(line);

	fclose(fp);
}

