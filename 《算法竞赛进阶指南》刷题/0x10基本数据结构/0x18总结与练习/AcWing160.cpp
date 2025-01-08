# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

int n, m, q;
char s1[NR], s2[NR];
int fail[NR], ans[NR];

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	scanf("%s%s", s1 + 1, s2 + 1);
	fail[0] = fail[1] = 0;
	for (int i = 2, j = 0; i <= m; i++) {
		while (j && s2[i] != s2[j + 1]) j = fail[j];
		if (s2[i] == s2[j + 1]) j++;
		fail[i] = j;
	}
	for (int i = 1, j = 0; i <= n; i++) {
		while (j && s1[i] != s2[j + 1]) j = fail[j];
		if (s1[i] == s2[j + 1]) j++;
		ans[j]++;
	}
	for (int i = m; i >= 1; i--)
		ans[fail[i]] += ans[i];
	while (q--) {
		int x;
		scanf("%d", &x);
		printf("%d\n", ans[x] - ans[x + 1]);
	}
	return 0;
}