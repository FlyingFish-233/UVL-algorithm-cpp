// AcWing141 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n;
char s[NR];
int fail[NR];

void getFail()
{
	for (int i = 2, j = 0; i <= n; i++) {
		while (j > 0 && s[j + 1] != s[i]) j = fail[j];
		if (s[j + 1] == s[i]) j++;
		fail[i] = j;
	}
}

// if 循环元长度len = i-fail(n)[i] 整除 i, then s[1~(i-fail(n)[i])]为s[1~i]的循环元
// fail(n)[i]指fail[i]迭代n次
int main()
{
	for (int t = 1; ; t++) {
		scanf("%d", &n);
		if (n == 0) break;
		scanf("%s", s + 1);
		getFail();
		printf("Test case #%d\n", t);
		for (int i = 1; i <= n; i++)
			if (i % (i - fail[i]) == 0 && fail[i])
				printf("%d %d\n", i, i / (i - fail[i]));
		puts("");
	}
	return 0;
}