# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e3 + 10, MR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int to, next, w, c;
};

int n, k, s, t;
int gsz = 1, fte[NR];
Edge g[MR << 1];

queue <int> q;
int head[NR], dis[NR];
bool already[NR], flag[NR];

int id(int x, int y, int t)
{
	return x * n + y + t * n * n;
}

void addEdge(int x, int y, int w, int c)
{
	g[++gsz] = (Edge) {y, fte[x], w, c}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], 0, -c}, fte[y] = gsz;
}

bool spfa()
{
	memset(dis, -0x3f, sizeof(dis));
	memcpy(head, fte, sizeof(fte));
	q.push(s), dis[s] = 0, already[s] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		already[x] = false;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (g[i].w == 0 || dis[y] >= dis[x] + g[i].c) continue;
			dis[y] = dis[x] + g[i].c;
			if (!already[y]) q.push(y), already[y] = true;
		}
	}
	return dis[t] > -1e9;
}

int dicnic(int x, int lim)
{
	if (x == t) return lim;
	int flow = 0;
	flag[x] = true;
	for (int i = head[x]; i && flow < lim; i = g[i].next) {
		int y = g[i].to;
		if (flag[y] || g[i].w == 0 || dis[y] != dis[x] + g[i].c) continue;
		int delta = dicnic(y, min(lim - flow, g[i].w));
		if (delta == 0) dis[y] = -INF;
		else g[i].w -= delta, g[i ^ 1].w += delta, flow += delta;
		head[x] = i;
	}
	flag[x] = false;
	return flow;
}

int main()
{
	scanf("%d%d", &n, &k);
	s = 2 * n * n, t = s + 1;
	addEdge(s, id(0, 0, 0), k, 0);
	addEdge(id(n - 1, n - 1, 1), t, k, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0, x; j < n; j++) {
			scanf("%d", &x);
			addEdge(id(i, j, 0), id(i, j, 1), 1, x);
			addEdge(id(i, j, 0), id(i, j, 1), INF, 0);
			if (i + 1 < n) addEdge(id(i, j, 1), id(i + 1, j, 0), INF, 0);
			if (j + 1 < n) addEdge(id(i, j, 1), id(i, j + 1, 0), INF, 0);
		}
	int ans = 0;
	while (spfa()) ans += dis[t] * dicnic(s, INF);
	printf("%d\n", ans);
	return 0;
}