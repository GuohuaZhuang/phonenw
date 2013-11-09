
#ifndef _PHONENW_PHONENW_H_
#define _PHONENW_PHONENW_H_

#include "trie.h"

extern const char* num_alpha_corres[];
// = {
// 	"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
// };

extern const int num_alpha_count[];
// = {
// 	0, 0, 3, 3, 3, 3, 3, 4, 3, 4
// };

int search(const char* word);

void PrintComb(int* num_group, int* alpha_index_group, int n);

int PrintAllComb(int* num_group, int* alpha_index_group, int n);

int GeneratePhoneNumberWords(const char* input);

#endif // _PHONENW_PHONENW_H_

