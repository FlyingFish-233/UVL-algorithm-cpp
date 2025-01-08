// AcWing176 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e3 + 10, MR = 1e4 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, a[NR];
int gsz, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

struct Node
{
	int x, c, w;
	bool operator < (const Node &cmp) const {
		return w > cmp.w;
	}
};

int f[NR][NR];
bool flag[NR][NR];

int dijkstra(int C, int S, int E)
{
	priority_queue<Node> q;
	memset(f, 0x3f, sizeof(f));
	memset(flag, false, sizeof(flag));
	q.push((Node) {S, 0, f[S][0] = 0});
	while (!q.empty()) {
		int x = q.top().x, c = q.top().c;
		q.pop();
		if (x == E) return f[x][c];
		if (flag[x][c]) continue;
		flag[x][c] = true;
		if (c + 1 <= C && f[x][c + 1] > f[x][c] + a[x])
			q.push((Node) {x, c + 1, f[x][c + 1] = f[x][c] + a[x]});
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (c >= g[i].w && f[y][c - g[i].w] > f[x][c])
				q.push((Node) {y, c - g[i].w, f[y][c - g[i].w] = f[x][c]});
		}
	}
	return -1;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		addEdge(x, y, w);
		addEdge(y, x, w);
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int C, S, E;
		scanf("%d%d%d", &C, &S, &E);
		int ans = dijkstra(C, S, E);
		if (ans == -1) printf("impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}