// P3375 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int len1, len2;
char s1[NR], s2[NR];
int fail[NR];

void getFail()
{
	for (int i = 2, j = 0; i <= len2; i++) {
		while (j > 0 && s2[i] != s2[j + 1]) j = fail[j];
		if (s2[i] == s2[j + 1]) j++;
		fail[i] = j;
	}
}

int main()
{
	scanf("%s%s", s1 + 1, s2 + 1);
	len1 = strlen(s1 + 1), len2 = strlen(s2 + 1); getFail();
	for (int i = 1, j = 0; i <= len1; i++) {
		while (j > 0 && s1[i] != s2[j + 1]) j = fail[j];
		if (s1[i] == s2[j + 1]) j++;
		if (j == len2) printf("%d\n", i - len2 + 1);
	}
	for (int i = 1; i <= len2; i++)
		printf("%d ", fail[i]);
	puts("");
	return 0;
}