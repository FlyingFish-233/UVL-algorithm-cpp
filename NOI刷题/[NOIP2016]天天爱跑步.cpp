// P1600 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 3e5 + 10;

struct Edge
{
	int to, next;
};

int n, m, w[NR];
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y)
{
	g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz;
}

int fa[NR][30], dep[NR];

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = fte[x]; i; i = g[i].next)
		if (g[i].to != dad) build(g[i].to, x);
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

vector<int> a1[NR], b1[NR], a2[NR], b2[NR];
int c1[NR << 1], c2[NR << 1], ans[NR];

void dfs(int x, int dad)
{
	int t1 = c1[w[x] + dep[x]], t2 = c2[w[x] - dep[x] + n];
	for (int i = fte[x]; i; i = g[i].next)
		if (g[i].to != dad) dfs(g[i].to, x);
	for (int i = 0; i < (int) a1[x].size(); i++) c1[a1[x][i]]++;
	for (int i = 0; i < (int) b1[x].size(); i++) c1[b1[x][i]]--;
	for (int i = 0; i < (int) a2[x].size(); i++) c2[a2[x][i] + n]++;
	for (int i = 0; i < (int) b2[x].size(); i++) c2[b2[x][i] + n]--;
	ans[x] += c1[w[x] + dep[x]] - t1 + c2[w[x] - dep[x] + n] - t2;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), addEdge(x, y);
	dep[0] = 1, build(1, 0);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y);
		int z = lca(x, y);
		a1[x].push_back(dep[x]);
		b1[fa[z][0]].push_back(dep[x]);
		a2[y].push_back(dep[x] - 2 * dep[z]);
		b2[z].push_back(dep[x] - 2 * dep[z]);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
}