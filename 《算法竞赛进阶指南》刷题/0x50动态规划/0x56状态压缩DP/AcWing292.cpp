# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 6e4 + 10;

int n, m;
char c[NR][NR];
int p[20], f[NR][MR];

void dfs(int row, int i, int sta, int sta0, int delta)
{
	if (i == m) { f[row + 1][sta0] = max(f[row + 1][sta0], f[row][sta] + delta); return; }
	int t = sta / p[i] % 3;
	if (t >= 1) { dfs(row, i + 1, sta, sta0 + (t - 1) * p[i], delta); return; }
	dfs(row, i + 1, sta, sta0, delta);
	if (c[row + 1][i] == 'H') return;
	if (i - 1 >= 0 && sta0 / p[i - 1] % 3 == 2) return;
	if (i - 2 >= 0 && sta0 / p[i - 2] % 3 == 2) return;
	dfs(row, i + 1, sta, sta0 + 2 * p[i], delta + 1);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", c[i]);

	p[0] = 1;
	for (int i = 1; i <= m; i++)
		p[i] = p[i - 1] * 3;

	memset(f, -0x3f, sizeof(f));
	f[0][0] = 0;

	for (int i = 0; i < n; i++)
		for (int sta = 0; sta <= p[m] - 1; sta++)
			if (f[i][sta] >= 0) dfs(i, 0, sta, 0, 0);
	int ans = 0;
	for (int sta = 0; sta <= p[m] - 1; sta++)
		ans = max(ans, f[n][sta]);
	printf("%d\n", ans);
	return 0;
}