# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20, MR = (1 << 12) + 10;
const int INF = 0x3f3f3f3f;

int n, m, lim;
int g[NR][NR];
int expand[MR], cost[MR][NR];
int f[NR][MR];

int main()
{
	scanf("%d%d", &n, &m);
	lim = (1 << n) - 1;
	memset(g, 0x3f, sizeof(g));
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w), x--, y--;
		g[x][y] = g[y][x] = min(g[x][y], w);
	}

	memset(cost, 0x3f, sizeof(cost));
	for (int sta = 0; sta <= lim; sta++)
		for (int i = 0; i < n; i++) if (sta >> i & 1)
			for (int j = 0; j < n; j++) if (!(sta >> j & 1) && g[i][j] < INF)
				expand[sta] |= 1 << j, cost[sta][j] = min(cost[sta][j], g[i][j]);

	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < n; i++)
		f[1][1 << i] = 0;
	for (int i = 1; i < n; i++)
		for (int pre = 0; pre < lim; pre++)
			for (int sta = expand[pre]; sta > 0; sta = (sta - 1) & expand[pre]) {
				int delta = 0;
				for (int j = 0; j < n; j++)
					if (sta >> j & 1) delta += cost[pre][j];
				f[i + 1][pre | sta] = min(f[i + 1][pre | sta], f[i][pre] + i * delta);
			}
	int ans = INF;
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i][lim]);
	printf("%d\n", ans);
	return 0;
}