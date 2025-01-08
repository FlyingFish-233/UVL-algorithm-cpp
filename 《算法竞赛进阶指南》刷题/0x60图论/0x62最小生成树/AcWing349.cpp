# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1000 + 10;
const long long mod = (1ll << 31) - 1;

int n, m;
int g[NR][NR];
int dis[NR], s[NR];
bool flag[NR];

int main()
{
	memset(g, 0x3f, sizeof(g));
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y, w; i <= m; i++)
		scanf("%d%d%d", &x, &y, &w), g[x][y] = g[y][x] = min(g[x][y], w);
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0, s[1] = 1;
	for (int i = 1; i < n; i++) {
		int x = 0;
		for (int j = 1; j <= n; j++)
			if (!flag[j] && (x == 0 || dis[j] < dis[x])) x = j;
		flag[x] = true;
		for (int y = 1; y <= n; y++) if (!flag[y]) {
			if (dis[y] == dis[x] + g[x][y]) s[y]++;
			if (dis[y] > dis[x] + g[x][y]) dis[y] = dis[x] + g[x][y], s[y] = 1;
		}
	}
	long long ans = 1;
	for (int i = 1; i <= n; i++)
		(ans *= s[i]) %= mod;
	printf("%lld\n", ans);
	return 0;
}