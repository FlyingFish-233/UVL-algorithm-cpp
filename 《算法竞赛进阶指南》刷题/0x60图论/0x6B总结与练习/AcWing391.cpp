# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 5e5 + 10;

struct Edge
{
	int to, next;
};

int n, m;
vector<int> g[NR];
int dep[NR], fa[NR][30];

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

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	dep[1] = 1, build(1, 0);
	while (m--) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		int a = lca(y, z), b = lca(x, z), c = lca(x, y), sum = dep[x] + dep[y] + dep[z];
		if (a == b && b == c) {
			printf("%d %d\n", a, sum - 3 * dep[a]);
			continue;
		}
		if (a == b) printf("%d %d\n", c, sum - dep[c] - 2 * dep[a]);
		if (b == c) printf("%d %d\n", a, sum - dep[a] - 2 * dep[b]);
		if (c == a) printf("%d %d\n", b, sum - dep[b] - 2 * dep[c]);
	}
	return 0;
}