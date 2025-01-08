# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 5e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int to, next, w;
};

int n, S;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

int q[NR], dis[NR], pre[NR];
vector< pair<int, int> > path;

int bfs(int s)
{
	int p = s, l = 1, r = 0;
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = pre[s] = 0, q[++r] = s;
	while (l <= r) {
		int x = q[l++];
		if (dis[x] > dis[p]) p = x;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dis[y] == INF)
				dis[y] = dis[x] + g[i].w, pre[y] = x, q[++r] = y;
		}
	}
	return p;
}

bool flag[NR];
int d_max;

void dfs(int x, int fa)
{
	d_max = max(d_max, dis[x]);
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y != fa) dis[y] = dis[x] + g[i].w, dfs(y, x);
	}
}

int main()
{
	scanf("%d%d", &n, &S);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
	int u = bfs(1), v = bfs(u);
	for (int x = v; x; x = pre[x])
		path.push_back({x, dis[x]}), flag[x] = true;
	reverse(path.begin(), path.end());

	for (int x = v; x; x = pre[x])
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (!flag[y]) dis[y] = g[i].w, dfs(y, x);
		}
	int ans = 2e9;
	for (int i = 0, j = 0; i < (int) path.size(); i++) {
		while (j + 1 < (int) path.size() && path[j + 1].second - path[i].second <= S) j++;
		ans = min(ans, max(d_max, max(path[i].second, path.back().second - path[j].second)));
	}
	printf("%d\n", ans);
	return 0;
}