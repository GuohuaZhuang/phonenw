
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char* num_alpha_corres[10] = {
	"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};
const int num_alpha_count[10] = {
	0, 0, 3, 3, 3, 3, 3, 4, 3, 4
};

static int search(const char* word);

void PrintComb(int* num_group, int* alpha_index_group, int n)
{
	char* word = malloc(256);
	memset(word, 0, 256);
	int _i = 0, i = 0;
	for (i = 0; i < n; i ++) {
		char c = num_alpha_corres[num_group[i]][alpha_index_group[i]];
		if (0 != c) {
			// printf("%c", c);
			word[_i++] = c;
		}
	}
	// printf("\n");
	if (search(word) > 0) printf("%s\n", word);
	free(word);
}

int PrintAllComb(int* num_group, int* alpha_index_group, int n)
{
	while (1) {
		PrintComb(num_group, alpha_index_group, n);
		int _i = n - 1;
		while (_i >= 0) {
			if (alpha_index_group[_i] < (num_alpha_count[num_group[_i]]-1)) {
				alpha_index_group[_i] ++;
				break;
			} else {
				alpha_index_group[_i] = 0;
				_i --;
			}
		}
		if (_i < 0) break;
	}
	return 0;
}

int GeneratePhoneNumberWords(const char* input)
{
	// 存放号码数组
	int* num_group = NULL;
	// 存放字母索引
	int* alpha_index_group = NULL;

	int n_len = strlen(input);
	num_group = (int*)malloc(sizeof(int)*n_len);
	alpha_index_group = (int*)malloc(sizeof(int)*n_len);
	int i = 0;
	for (i = 0; i < n_len; i ++) {
		num_group[i] = input[i] - '0';
		alpha_index_group[i] = 0;
	}
	// DEBUG
	printf("You input n_len = %d, and the number is: ", n_len);
	int _i = 0;
	for (_i = 0; _i < n_len; _i ++) {
		printf("%d", num_group[_i]);
	}
	printf("\n");
	// ENDDEBUG
	PrintAllComb(num_group, alpha_index_group, n_len);

	return 0;
}

#define TREE_WIDTH 256
#define WORDLENMAX 128
 
struct trie_node_st {
    int count;
    int pass; //add a count for the part-include for example 'this is' then the 'is' is hited tow times 
    struct trie_node_st *next[TREE_WIDTH];
};
 
static struct trie_node_st root={0, 0, {NULL}};
 
// static char *spaces=" \t\r\n/.\"\'()";
 
static int
insert(const char *word)
{
    int i;
    struct trie_node_st *curr, *newnode;
 
    if (word[0]=='\0') {
        return 0;
    }
    curr = &root;
    for (i=0; ; ++i) {
        if (word[i] == '\0') {
            break;
        }
        curr->pass++;//count
        if (curr->next[ (int)word[i] ] == NULL) {
            newnode=(struct trie_node_st*)malloc(sizeof(struct trie_node_st));
            memset(newnode, 0, sizeof(struct trie_node_st));
            curr->next[ (int)word[i] ] = newnode;
        } 
        curr = curr->next[ (int)word[i] ];
    }
    curr->count ++;
 
    return 0;
}

static int search(const char* word)
{
	int i;
	struct trie_node_st *curr;
	curr = &root;
	if (word[0] == '\0' || NULL == curr) {
		return 0;
	}
	for (i = 0; ; ++i) {
		if (word[i] == '\0') {
			return curr->count;
		}
		if (curr->next[ (int)word[i] ] == NULL) {
			return 0;
		}
		curr = curr->next[ (int)word[i] ];
	}
	return curr->count;
}
 
static void
printword(const char *str, int n)
{
    printf("%s\t%d\n", str, n);
}
 
static int
do_travel(struct trie_node_st *rootp)
{
    static char worddump[WORDLENMAX+1];
    static int pos=0;
    int i;
 
    if (rootp == NULL) {
        return 0;
    }
    if (rootp->count) {
        worddump[pos]='\0';
        printword(worddump, rootp->count/*+rootp->pass*/);
    }
    for (i=0;i<TREE_WIDTH;++i) {
        worddump[pos++]=i;
        do_travel(rootp->next[i]);
        pos--;
    }
    return 0;
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

