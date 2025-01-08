# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 6000 + 10;

struct Edge
{
	int u, v, w;
	bool operator < (const Edge &cmp) const {
		return w < cmp.w;
	}
};

int n;
Edge g[NR];
int fa[NR], sz[NR];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	sz[y] += sz[x], fa[x] = y;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n - 1; i++)
			scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
		for (int i = 1; i <= n; i++)
			fa[i] = i, sz[i] = 1;
		sort(g + 1, g + (n - 1) + 1);
		long long ans = 0;
		for (int i = 1; i <= n - 1; i++) {
			int x = find(g[i].u), y = find(g[i].v);
			if (x != y) ans += 1ll * (g[i].w + 1) * (sz[x] * sz[y] - 1), merge(x, y);
		}
		printf("%lld\n", ans);
	}
	return 0;
}