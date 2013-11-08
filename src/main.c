
#include "trie.h"
#include "phonenw.h"

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static void
printword(const char *str, int n)
{
    printf("%s\t%d\n", str, n);
}
 

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
		if (line[read-1] == '\n') line[read-1] = '\0';
		if (line[read-2] == '\r') line[read-2] = '\0';
        insert(line);
	}
	free(line);
	fclose(fp);

	printf("Please input your phone number:");
	char input[1024] = {0};
	scanf("%s[0-9]", input);
	printf("You be sure to input the phone number: [%s]\n", input);
	int _i = 0, _len = strlen(input);
	for (_i = 0; _i < _len; _i++) {
		if (!isdigit(input[_i])) {
			printf("You should put all number!, not %s\n", input);
			return -1;
		}
	}
	GeneratePhoneNumberWords(input);

	return 0;
}

