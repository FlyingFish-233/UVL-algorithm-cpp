# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long LL;

const int NR = 1e6 + 10, PR = 131;

int n;
char s[NR];
LL f[NR], p[NR];

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] * PR + s[i] - 'a';

	p[0] = 1;
	for (int i = 1; i <= n; i++)
		p[i] = p[i - 1] * PR;

	int T;
	scanf("%d", &T);
	while (T--) {
		int l1, r1, l2, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		LL x = f[r1] - f[l1 - 1] * p[r1 - l1 + 1];
		LL y = f[r2] - f[l2 - 1] * p[r2 - l2 + 1];
		printf("%s\n", (x == y) ? "Yes" : "No");
	}
	return 0;
}