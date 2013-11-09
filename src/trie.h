
#ifndef _PHONENW_TRIE_H_
#define _PHONENW_TRIE_H_

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
 
extern struct trie_node_st root;
// ={0, 0, {NULL}};

int insert(const char *word);

int search(const char* word);

int do_travel(struct trie_node_st *rootp);

void printword(const char *str, int n);

#endif // _PHONENW_TRIE_H_ 

