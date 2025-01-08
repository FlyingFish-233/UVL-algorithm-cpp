// P3379 (100 pts)
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

int n, m, root;
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
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	build(root, 0);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", lca(x, y));
	}
	return 0;
}