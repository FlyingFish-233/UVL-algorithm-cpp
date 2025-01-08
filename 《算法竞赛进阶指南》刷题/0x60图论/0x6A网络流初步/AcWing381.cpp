# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <stack>

using namespace std;

const int NR = 210, MR = 1e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, s, t;
int gsz, fte[NR];
Edge g[MR << 1], G[MR << 1];

void addEdge(int x, int y, int w)
{
	G[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	G[++gsz] = (Edge) {x, fte[y], 0}, fte[y] = gsz;
}

int dep[NR], head[NR];
queue <int> q;

bool bfs()
{
	while (!q.empty()) q.pop();
	memcpy(head, fte, sizeof(fte));
	memset(dep, 0, sizeof(dep));
	dep[s] = 1, q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (g[i].w == 0 || dep[y]) continue;
			dep[y] = dep[x] + 1;
			q.push(y);
			if (y == t) return true;
		}
	}
	return false;
}

int dfs(int x, int lim)
{
	if (x == t) return lim;
	int flow = 0;
	for (int i = head[x]; i && flow < lim; i = g[i].next) {
		int y = g[i].to;
		if (g[i].w == 0 || dep[y] != dep[x] + 1) continue;
		int delta = dfs(y, min(lim - flow, g[i].w));
		if (delta == 0) dep[y] = 0;
		else g[i].w -= delta, g[i ^ 1].w += delta, flow += delta;
	}
	return flow;
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(fte, 0, sizeof(fte)), gsz = 1;
		for (int i = 1, x, y; i <= m; i++) {
			char c; cin >> c;
			scanf("%d,%d", &x, &y), cin >> c;
			addEdge((++x) + n, ++y, 1e9);
			addEdge(y + n, x, 1e9);
		}
		for (int i = 1; i <= n; i++)
			addEdge(i, i + n, 1);
		int ans = n;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++) {
				s = i + n, t = j;
				memcpy(g, G, sizeof(G));
				int maxflow = 0;
				while (bfs()) maxflow += dfs(s, 1e9);
				ans = min(ans, maxflow);
			}
		printf("%d\n", ans);
	}
	return 0;
}