// LOJ136 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int PR = 1e9 + 7;

struct Edge
{
	int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

struct Array
{
	int u, v, w;
	bool operator < (const Array &cmp) const {
		return w < cmp.w;
	}
};

int tmp[NR];
Array e[NR];
bool used[NR];

int find(int x)
{
	if (tmp[x] == x) return x;
	return tmp[x] = find(tmp[x]);
}

void merge(int x, int y)
{
	tmp[find(x)] = find(y);
}

int fa[NR][30], dep[NR];
int f[NR][30];

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1], f[x][i] = max(f[x][i - 1], f[fa[x][i - 1]][i - 1]);
	for (int i = fte[x]; i; i = g[i].next) if (g[i].to != dad)
		f[g[i].to][0] = g[i].w, build(g[i].to, x);
}

int lca(int x, int y)
{
	if (dep[x] > dep[y]) swap(x, y);
	int save = -2e9;
	for (int i = 20; i >= 0; i--) if (dep[fa[y][i]] >= dep[x])
		save = max(save, f[y][i]), y = fa[y][i];
	if (x == y) return save;
	for (int i = 20; i >= 0; i--) if (fa[x][i] != fa[y][i])
		save = max(save, max(f[x][i], f[y][i])), x = fa[x][i], y = fa[y][i];
	return max(save, max(f[x][0], f[y][0]));
}

int main()
{
	int T;
	scanf("%d%d%d", &n, &m, &T);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++) tmp[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) merge(x, y), used[i] = true;
	}
	for (int i = 1; i <= m; i++)
		if (used[i]) addEdge(e[i].u, e[i].v, e[i].w);
	f[1][0] = -2e9, build(1, 0);
	while (T--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (find(x) != find(y)) printf("-1\n");
		else printf("%d\n", lca(x, y));
	}
	return 0;
}