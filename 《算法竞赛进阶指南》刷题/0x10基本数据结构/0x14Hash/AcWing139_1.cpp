# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long LL;

const int NR = 2e6 + 10, PR = 131;

int n;
char c[NR], s[NR];
LL f[NR], f0[NR], p[NR];

void init()
{
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] * PR + s[i] - 'a';
	f0[n + 1] = 0;
	for (int i = n; i >= 1; i--)
		f0[i] = f0[i + 1] * PR + s[i] - 'a';
	p[0] = 1;
	for (int i = 1; i <= n; i++)
		p[i] = p[i - 1] * PR;
}

int check(int l, int r)
{
	return f[r] - f[l - 1] * p[r - l + 1] == f0[l] - f0[r + 1] * p[r - l + 1];
}


int main()
{
	for (int t = 1; ; t++) {
		scanf("%s", c + 1);
		if (c[1] == 'E') break;

		int len = strlen(c + 1);
		s[n = 1] = '#';
		for (int i = 1; i <= len; i++)
			s[++n] = c[i], s[++n] = '#';
		init();

		int ans = 1;
		for (int i = 1; i <= n; i++)
			while (i - ans >= 1 && i + ans <= n && check(i - ans, i + ans)) ans++;
		printf("Case %d: %d\n", t, ans - 1);
	}
	return 0;
}