
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


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
 
