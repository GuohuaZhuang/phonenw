
#include <stdio.h>
#include <string.h>

const char* num_alpha_corres[10] = {
	"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};
const int num_alpha_count[10] = {
	0, 0, 3, 3, 3, 3, 3, 4, 3, 4
};


void PrintComb(int* num_group, int* alpha_index_group, int n)
{
	for (int i = 0; i < n; i ++) {
		char c = num_alpha_corres[num_group[i]][alpha_index_group[i]];
		if (0 != c) printf("%c", c);
	}
	printf("\n");
}

int PrintAllComb(int* num_group, int* alpha_index_group, int n)
{
	while (true) {
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
}

int main(int argc, char* argv[])
{
	// 存放号码数组
	int* num_group = NULL;
	// 存放字母索引
	int* alpha_index_group = NULL;

	printf("Please input your phone number:");
	char input[1024] = {0};
	scanf("%s[0-9]", input);
	printf("You be sure to input the phone number: [%s]\n", input);
	int n_len = strlen(input);
	num_group = new int[n_len];
	alpha_index_group = new int[n_len];
	for (int i = 0; i < n_len; i ++) {
		num_group[i] = input[i] - '0';
		alpha_index_group[i] = 0;
	}
	// DEBUG
	printf("You input n_len = %d, and the number is: ", n_len);
	for (int _i = 0; _i < n_len; _i ++) {
		printf("%d", num_group[_i]);
	}
	printf("\n");
	// ENDDEBUG
	PrintAllComb(num_group, alpha_index_group, n_len);

	return 0;
}


