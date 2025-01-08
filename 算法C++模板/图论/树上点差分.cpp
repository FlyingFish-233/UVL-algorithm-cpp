// P3258 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 3e5 + 10;

int n;
int a[NR];
vector<int> g[NR];
int fa[NR][30], dep[NR];

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < (int) g[x].size(); i++)
		if (g[x][i] != dad) build(g[x][i], x);
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

int d[NR];

void dfs(int x, int dad)
{
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (y != dad) dfs(y, x), d[x] += d[y];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	dep[0] = 1, build(1, 0);
	for (int i = 2; i <= n; i++) {
		int x = a[i - 1], y = a[i];
		d[x]++, d[y]++, d[lca(x, y)]--, d[fa[lca(x, y)][0]]--;
	}
	dfs(1, 0);
	for (int i = 2; i <= n; i++)
		d[a[i]]--;
	for (int i = 1; i <= n; i++)
		printf("%d\n", d[i]);
	return 0;
}