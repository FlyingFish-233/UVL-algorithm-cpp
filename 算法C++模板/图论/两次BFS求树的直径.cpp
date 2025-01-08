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

int n;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

queue<int> q;
int dis[NR];

int bfs(int s)
{
	int p = s;
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0, q.push(s);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		if (dis[x] > dis[p]) p = x;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dis[y] == INF) dis[y] = dis[x] + g[i].w, q.push(y);
		}
	}
	return p;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w), addEdge(y, x, w);
	int p = bfs(1), q = bfs(p);
	printf("%d\n", dis[q]);
	return 0;
}