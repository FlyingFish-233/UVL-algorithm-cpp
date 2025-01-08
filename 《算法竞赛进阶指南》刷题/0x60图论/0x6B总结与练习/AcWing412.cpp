# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 210, MR = 210;

struct Edge
{
	int to, next, w;
};

int n, m, s, t;
int gsz = 1, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], 0}, fte[y] = gsz;
}

int head[NR], dep[NR];
queue <int> q;

bool bfs()
{
	while (!q.empty()) q.pop();
	memset(dep, 0, sizeof(dep));
	memcpy(head, fte, sizeof(fte));
	dep[s] = 1, q.push(s);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dep[y] != 0 || g[i].w == 0) continue;
			dep[y] = dep[x] + 1, q.push(y);
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
		if (dep[y] != dep[x] + 1 || g[i].w == 0) continue;
		int delta = dfs(y, min(lim - flow, g[i].w));
		if (delta == 0) dep[y] = 0;
		else g[i].w -= delta, g[i ^ 1].w += delta, flow += delta;
		head[x] = i;
	}
	return flow;
}

int main()
{
	scanf("%d%d", &m, &n), s = 1, t = n;
	for (int i = 1, x, y, w; i <= m; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
	int ans = 0;
	while (bfs()) ans += dfs(s, 2e9);
	printf("%d\n", ans);
	return 0;
}