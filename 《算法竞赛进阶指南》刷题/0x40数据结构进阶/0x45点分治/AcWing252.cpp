# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

struct Edge
{
	int to, next, w;
};

int n, k;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

bool vis[NR];
int all, root;
int sz[NR], f[NR];

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

int dis[NR], len, tot;
pair<int, int> t[NR];

void dfs(int x, int fa)
{
	t[++len] = {dis[x], tot};
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa || vis[y]) continue;
		dis[y] = dis[x] + g[i].w;
		dfs(y, x);
	}
}

int ans, cnt[NR];

void calc(int x)
{
	len = tot = 0;
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (!vis[y]) ++tot, dis[y] = g[i].w, dfs(y, x);
	}
	t[++len] = {0, ++tot};
	sort(t + 1, t + len + 1);
	for (int i = 1; i <= len; i++)
		cnt[t[i].second]++;
	for (int l = 1, r = len; l < r; l++) {
		cnt[t[l].second]--;
		while (l < r && t[l].first + t[r].first > k)
			cnt[t[r--].second]--;
		ans += r - l - cnt[t[l].second];
	}
	for (int i = 1; i <= len; i++)
		cnt[t[i].second] = 0;
}

void solve(int x)
{
	vis[x] = true;
	calc(x);
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (vis[y]) continue;
		root = 0, all = sz[y];
		getRoot(y, x);
		solve(root);
	}
}

int main()
{
	while (scanf("%d%d", &n, &k) && !(n == 0 && k == 0)) {
		gsz = ans = 0;
		memset(fte, 0, sizeof(fte));
		for (int i = 1; i <= n - 1; i++) {
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			x++, y++;
			addEdge(x, y, w);
			addEdge(y, x, w);
		}
		memset(vis, false, sizeof(vis));
		f[root = 0] = 2e9, all = n;
		getRoot(1, 0);
		solve(root);
		printf("%d\n", ans);
	}
	return 0;
}