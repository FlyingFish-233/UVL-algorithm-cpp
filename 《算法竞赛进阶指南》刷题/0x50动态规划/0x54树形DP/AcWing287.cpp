# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

struct Edge
{
	int to, next;
	long long w;
};

int n;
int gsz, fte[NR], deg[NR];
Edge g[NR << 1];
long long c[NR], f[NR];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

void dfs(int x, int fa)
{
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa) continue;
		dfs(y, x);
		if (deg[y] == 1) c[x] += g[i].w;
		else c[x] += min(g[i].w, c[y]);
	}
}

void change(int x, int fa)
{
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa) continue;
		if (deg[x] == 1 && deg[y] == 1) f[y] = g[i].w;
		if (deg[x] == 1 && deg[y] != 1) f[y] = c[y] + g[i].w;
		if (deg[x] != 1 && deg[y] == 1) f[y] = min(g[i].w, f[x] - g[i].w);
		if (deg[x] != 1 && deg[y] != 1) f[y] = c[y] + min(g[i].w, f[x] - min(g[i].w, c[y]));
		change(y, x);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		gsz = 0;
		memset(fte, 0, sizeof(fte));
		memset(deg, 0, sizeof(deg));
		memset(c, 0, sizeof(c));
		scanf("%d", &n);
		for (int i = 1; i <= n - 1; i++) {
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			addEdge(x, y, w);
			addEdge(y, x, w);
			deg[x]++, deg[y]++;
		}
		dfs(1, 0);
		f[1] = c[1], change(1, 0);
		long long ans = 0;
		for (int i = 1; i <= n; i++)
			ans = max(ans, f[i]);
		printf("%lld\n", ans);
	}
	return 0;
}