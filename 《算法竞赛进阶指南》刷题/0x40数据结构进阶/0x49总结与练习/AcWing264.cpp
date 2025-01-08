# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10, MR = 1e6 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int to, next, w;
};

int n, k;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

int root;
int all, sz[NR], f[NR];
bool vis[NR];

void getRoot(int x, int fa)
{
	sz[x] = 1, f[x] = 0;
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa || vis[y]) continue;
		getRoot(y, x);
		sz[x] += sz[y];
		f[x] = max(f[x], sz[y]);
	}
	f[x] = max(f[x], all - sz[x]);
	if (f[root] > f[x]) root = x;
}

int ans = 2e9;
int dep[NR], w_sum[NR];
int len, t1[NR], t2[NR];
int d_min[MR], save[NR];

void dfs(int x, int fa)
{
	if (w_sum[x] > k) w_sum[x] = k + 1;
	else t1[++len] = dep[x], t2[len] = w_sum[x];
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa || vis[y]) continue;
		dep[y] = dep[x] + 1;
		w_sum[y] = w_sum[x] + g[i].w;
		dfs(y, x);
	}
}

void calc(int x)
{
	int tot = 0; d_min[0] = 0;
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (vis[y]) continue;
		len = 0, dep[y] = 1, w_sum[y] = g[i].w;
		dfs(y, x);
		for (int j = 1; j <= len; j++)
			ans = min(ans, d_min[k - t2[j]] + t1[j]);
		for (int j = 1; j <= len; j++)
			d_min[t2[j]] = min(d_min[t2[j]], t1[j]);
		for (int j = 1; j <= len; j++)
			save[++tot] = t2[j];
	}
	for (int i = 1; i <= tot; i++)
		d_min[save[i]] = INF;
}

void solve(int x)
{
	vis[x] = true;
	calc(x);
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (vis[y]) continue;
		root = 0, all = sz[y];
		getRoot(y, x), solve(root);
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(++x, ++y, w);
	memset(d_min, 0x3f, sizeof(d_min));
	f[root = 0] = 2e9, all = n;
	getRoot(1, 0), solve(root);
	if (ans >= n) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}