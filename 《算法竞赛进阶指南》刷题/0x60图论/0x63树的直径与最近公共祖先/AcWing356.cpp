# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef pair<int, int> PII;

const int NR = 1e5 + 10;

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
Array e[NR << 2];
bool used[NR << 2];

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
PII f[NR][30];

PII pair_max(PII x, PII y)
{
	int save = max(x.second, y.second);
	if (x.first < y.first) save = max(x.first, y.second);
	if (x.first > y.first) save = max(x.second, y.first);
	return {max(x.first, y.first), save};
}

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1, f[x][0].second = -2e9;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1], f[x][i] = pair_max(f[x][i - 1], f[fa[x][i - 1]][i - 1]);
	for (int i = fte[x]; i; i = g[i].next) if (g[i].to != dad)
		f[g[i].to][0].first = g[i].w, build(g[i].to, x);
}

PII lca(int x, int y)
{
	if (dep[x] > dep[y]) swap(x, y);
	PII save = {-2e9, -2e9};
	for (int i = 20; i >= 0; i--) if (dep[fa[y][i]] >= dep[x])
		save = pair_max(save, f[y][i]), y = fa[y][i];
	if (x == y) return save;
	for (int i = 20; i >= 0; i--) if (fa[x][i] != fa[y][i])
		save = pair_max(save, pair_max(f[x][i], f[y][i])), x = fa[x][i], y = fa[y][i];
	return save = pair_max(save, pair_max(f[x][0], f[y][0]));
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e + 1, e + m + 1);
	long long sum = 0;
	for (int i = 1; i <= n; i++) tmp[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) sum += e[i].w, merge(x, y), used[i] = true;
	}
	for (int i = 1; i <= m; i++)
		if (used[i]) addEdge(e[i].u, e[i].v, e[i].w);
	dep[0] = 1, f[1][0].first = -2e9, build(1, 0);
	long long ans = 1e18;
	for (int i = 1; i <= m; i++) if (!used[i]) {
		PII save = lca(e[i].u, e[i].v);
		if (e[i].w > save.first) ans = min(ans, sum - save.first + e[i].w);
		if (e[i].w == save.first) ans = min(ans, sum - save.second + e[i].w);
	}
	printf("%lld\n", ans);
	return 0;
}