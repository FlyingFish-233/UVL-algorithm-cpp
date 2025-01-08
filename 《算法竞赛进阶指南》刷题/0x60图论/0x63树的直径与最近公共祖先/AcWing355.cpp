# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>

using namespace std;

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

int fa[NR][30], dep[NR];
int cnt, dfn[NR];
long long dis[NR];

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1, dfn[x] = ++cnt;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = fte[x]; i; i = g[i].next) if (g[i].to != dad)
		dis[g[i].to] = dis[x] + g[i].w, build(g[i].to, x);
}

int lca(int x, int y)
{
	if (dep[x] > dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (dep[fa[y][i]] >= dep[x]) y = fa[y][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i--)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

long long ans;
set< pair<int, int> > s;

long long dist(int x, int y)
{
	return dis[x] + dis[y] - 2 * dis[lca(x, y)];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
	dep[0] = 1, build(1, 0);
	scanf("%d", &m);
	while (m--) {
		char op; int x;
		cin >> op;
		if (op == '+') {
			scanf("%d", &x);
			if (s.empty()) { s.insert({dfn[x], x}); continue; }
			auto it1 = --s.lower_bound({dfn[x], x}), it2 = s.lower_bound({dfn[x], x});
			if (it2 == s.begin()) it1 = --s.end();
			if (it2 == s.end()) it2 = s.begin();
			ans -= dist(it1 -> second, it2 -> second);
			ans += dist(it1 -> second, x) + dist(it2 -> second, x);
			s.insert({dfn[x], x});
		}
		if (op == '-') {
			scanf("%d", &x);
			s.erase({dfn[x], x});
			if (s.empty()) continue;
			auto it1 = --s.lower_bound({dfn[x], x}), it2 = s.lower_bound({dfn[x], x});
			if (it2 == s.begin()) it1 = --s.end();
			if (it2 == s.end()) it2 = s.begin();
			ans -= dist(it1 -> second, x) + dist(it2 -> second, x);
			ans += dist(it1 -> second, it2 -> second);
		}
		if (op == '?') printf("%lld\n", ans >> 1);
	}
	return 0;
}