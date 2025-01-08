// P4298 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n, m;
bool adj[NR][NR];

int opp[NR];
bool vis[NR];

bool vx[NR], vy[NR];

bool flag[NR];

bool find(int x)
{
	if (vis[x]) return false;
	vis[x] = true;
	for (int y = 1; y <= n; y++)
		if (flag[y] && adj[x][y] && (opp[y] == 0 || find(opp[y]))) {
			opp[y] = x;
			return true;
		}
	return false;
}

int maxMatch()
{
	memset(opp, 0, sizeof(opp));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!flag[i]) continue;
		memset(vis, false, sizeof(vx));
		ans += find(i);
	}
	return ans;
}

void mark(int x)
{
	if (vx[x]) return;
	vx[x] = true;
	for (int y = 1; y <= n; y++)
		if (adj[x][y] && !vy[y] && opp[y]) {
			vy[y] = true;
			mark(opp[y]);
		}
}

// Dilworth定理:最长反链长度 = 最小链覆盖(最小路径可重复点覆盖)
// 定理:最小路径点覆盖 = n - 拆点二分图的最大匹配、
// 构造最长反链: 一个点属于最长反链 <=> 他在拆点二分图中的两点均属于最大独立集
int main()
{
	memset(flag, true, sizeof(flag));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x][y] = true;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				adj[i][j] |= (adj[i][k] && adj[k][j]);
	int ans = n - maxMatch();
	printf("%d\n", ans);

	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= n; i++)
		vis[opp[i]] = true;
	memset(vx, false, sizeof(vx));
	memset(vy, false, sizeof(vy));
	for (int i = 1; i <= n; i++)
		if (!vis[i]) mark(i);
	for (int i = 1; i <= n; i++)
		printf("%d", vx[i] && !vy[i]);
	puts("");

	for (int x = 1; x <= n; x++) {
		memset(flag, true, sizeof(flag));
		int num = 0;
		for (int y = 1; y <= n; y++)
			if (adj[x][y] || adj[y][x] || x == y) flag[y] = false;
			else num++;
		printf("%d", num - maxMatch() == ans - 1);
	}
	puts("");
	return 0;
}