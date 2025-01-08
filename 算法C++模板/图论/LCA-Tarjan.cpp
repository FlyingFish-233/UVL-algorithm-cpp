// P3379 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 5e5 + 10;

int n, m, root;
vector<int> g[NR];
vector< pair<int, int> > q[NR];

bool vis[NR];
int fa[NR], ans[NR];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void build(int x)
{
	vis[x] = true;
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (!vis[y]) build(y), fa[y] = x;
	}
	for (int i = 0; i < (int) q[x].size(); i++) {
		int y = q[x][i].first, id = q[x][i].second;
		if (vis[y]) ans[id] = find(y);
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	for (int i = 1, x, y; i <= m; i++)
		scanf("%d%d", &x, &y), q[x].push_back(make_pair(y, i)), q[y].push_back(make_pair(x, i));
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	build(root);
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}