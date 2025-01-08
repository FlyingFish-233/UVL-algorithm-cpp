// P4556 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
vector<int> g[NR];
int u[NR], v[NR], z[NR];
int cntz, idz[NR];

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

struct Node
{
	int ls, rs, max, pos;
};

int tot, root[NR];
Node tree[NR << 6];

void pushUp(int rt)
{
	if (tree[tree[rt].ls].max >= tree[tree[rt].rs].max)
		tree[rt].max = tree[tree[rt].ls].max, tree[rt].pos = tree[tree[rt].ls].pos;
	else  tree[rt].max = tree[tree[rt].rs].max, tree[rt].pos = tree[tree[rt].rs].pos;
}

void modify(int &rt, int l, int r, int x, int delta)
{
	if (rt == 0) rt = ++tot;
	if (l == r) { tree[rt].max += delta, tree[rt].pos = l; return; }
	int mid = (l + r) >> 1;
	if (x <= mid) modify(tree[rt].ls, l, mid, x, delta);
	else modify(tree[rt].rs, mid + 1, r, x, delta);
	pushUp(rt);
}

int merge(int x, int y, int l, int r)
{
	if (x == 0 || y == 0) return x + y;
	if (l == r) { tree[x].max += tree[y].max; return x; }
	int mid = (l + r) >> 1, rt = x;
	tree[rt].ls = merge(tree[x].ls, tree[y].ls, l, mid);
	tree[rt].rs = merge(tree[x].rs, tree[y].rs, mid + 1, r);
	pushUp(rt);
	return rt;
}

int ans[NR];

void dfs(int x, int dad)
{
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (y != dad) dfs(y, x), root[x] = merge(root[x], root[y], 1, cntz);
	}
	if (tree[root[x]].max > 0) ans[x] = idz[tree[root[x]].pos];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	dep[0] = 1, build(1, 0);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &u[i], &v[i], &z[i]);
	memcpy(idz, z, sizeof(z));
	sort(idz + 1, idz + m + 1);
	cntz = unique(idz + 1, idz + m + 1) - idz - 1;
	for (int i = 1; i <= m; i++) {
		int zt = lower_bound(idz + 1, idz + cntz + 1, z[i]) - idz, p = lca(u[i], v[i]);
		modify(root[u[i]], 1, cntz, zt, 1);
		modify(root[v[i]], 1, cntz, zt, 1);
		modify(root[p], 1, cntz, zt, -1);
		modify(root[fa[p][0]], 1, cntz, zt, -1);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}