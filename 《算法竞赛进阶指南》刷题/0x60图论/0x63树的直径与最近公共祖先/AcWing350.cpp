# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int to, next, w;
};

int n, k, len1, len2;
int gsz = 1, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

queue<int> q;
int dis[NR], pre[NR];

int bfs(int s)
{
	int p = s;
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = pre[s] = 0, q.push(s);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		if (dis[x] > dis[p]) p = x;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dis[y] == INF)
				dis[y] = dis[x] + g[i].w, pre[y] = i, q.push(y);
		}
	}
	return p;
}

void dfs(int x, int fa)
{
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa) continue;
		dfs(y, x);
		len2 = max(len2, dis[x] + dis[y] + g[i].w);
		dis[x] = max(dis[x], dis[y] + g[i].w);
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), addEdge(x, y, 1);
	int p = bfs(1), q = bfs(p);
	len1 = dis[q];
	for (int x = q; pre[x]; x = g[pre[x] ^ 1].to)
		g[pre[x]].w = g[pre[x] ^ 1].w = -1;
	memset(dis, 0, sizeof(dis));
	dfs(1, 0);
	if (k == 1) printf("%d\n", 2 * n  - len1 - 1);
	else printf("%d\n", 2 * n - len1 - len2);
	return 0;
}