// P4001 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e6 + 10, MR = 6e6 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, s, t;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

int p(int x, int y)
{
	return x * (m - 1) + y;
}

struct Node
{
	int x, d;

	bool operator < (const Node &cmp) const {
		return d > cmp.d;
	}
};

int dis[NR];
bool flag[NR];
priority_queue<Node> q;

void dijkstra()
{
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	q.push((Node) {s, dis[s]});
	while (!q.empty()) {
		int x = q.top().x;
		q.pop();
		if (flag[x]) continue;
		flag[x] = true;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dis[y] <= dis[x] + g[i].w) continue;
			dis[y] = dis[x] + g[i].w;
			q.push((Node) {y, dis[y]});
		}
	}
}

// 平面图: 最大流 = 最小割 = 对偶图最短路
int main()
{
	scanf("%d%d", &n, &m);
	const int sz = (n - 1) * (m - 1);
	s = sz << 1, t = s + 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m - 1; j++) {
			int x, y, w;
			scanf("%d", &w);
			if (i == 0) x = p(0, j), y = t;
			else if (i == n - 1) x = p(n - 2, j) + sz, y = s;
			else x = p(i - 1, j) + sz, y = p(i, j);
			addEdge(x, y, w);
			addEdge(y, x, w);
		}

	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < m; j++) {
			int x, y, w;
			scanf("%d", &w);
			if (j == 0) x = p(i, 0) + sz, y = s;
			else if (j == m - 1) x = p(i, m - 2), y = t;
			else x = p(i, j - 1), y = p(i, j) + sz;
			addEdge(x, y, w);
			addEdge(y, x, w);
		}

	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < m - 1; j++) {
			int x, y, w;
			scanf("%d", &w);
			x = p(i, j), y = p(i, j) + sz;
			addEdge(x, y, w);
			addEdge(y, x, w);
		}
	dijkstra();
	printf("%d\n", dis[t]);
	return 0;
}