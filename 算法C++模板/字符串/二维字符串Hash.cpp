// AcWing156 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long LL;

const int NR = 1e3 + 10, PR = 131, QR = 1331;

int n, m, a, b;
char c[NR];
LL f[NR][NR], g[NR][NR];
LL p[NR], q[NR], v[NR * NR];

int main()
{
	scanf("%d%d%d%d", &n, &m, &a, &b);
	p[0] = 1;
	for (int i = 1; i <= n; i++)
		p[i] = p[i - 1] * PR;
	q[0] = 1;
	for (int i = 1; i <= m; i++)
		q[i] = q[i - 1] * QR;

	for (int i = 1; i <= n; i++) {
		scanf("%s", c + 1);
		for (int j = 1; j <= m; j++)
			f[i][j] = f[i][j - 1] * QR + c[j] - '0';
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = f[i - 1][j] * PR + f[i][j];

	int cnt = 0;
	for (int i = a; i <= n; i++)
		for (int j = b; j <= m; j++)
			v[++cnt] = f[i][j] - f[i - a][j] * p[a] - f[i][j - b] * q[b] + f[i - a][j - b] * p[a] * q[b];
	sort(v + 1, v + cnt + 1);
	cnt = unique(v + 1, v + cnt + 1) - v;

	int T;
	scanf("%d", &T);
	while (T--) {
		for (int i = 1; i <= a; i++) {
			scanf("%s", c + 1);
			for (int j = 1; j <= b; j++)
				g[i][j] = g[i][j - 1] * QR + c[j] - '0';
		}
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
				g[i][j] = g[i - 1][j] * PR + g[i][j];
		printf("%d\n", binary_search(v + 1, v + cnt + 1, g[a][b]));
	}
	return 0;
}