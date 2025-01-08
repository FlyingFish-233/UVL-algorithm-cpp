# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e5 + 10;
const long long INF = 0x3f3f3f3f3f3f3f3f;

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
long long dis[NR];
int pre[NR], nxt[NR];

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
				dis[y] = dis[x] + g[i].w, pre[y] = x, q.push(y);
		}
	}
	return p;
}

bool flag[NR];
long long d_max, f[NR];

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
	scanf("%d", &n);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w), addEdge(y, x, w);
	int p = bfs(1), q = bfs(p);
	printf("%lld\n", dis[q]);
	for (int i = q; i; i = pre[i])
		flag[i] = true, nxt[pre[i]] = i;
	for (int x = q; x; x = pre[x]) {
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (flag[y]) continue;
			d_max = 0, dis[y] = g[i].w;
			dfs(y, x), f[x] = max(f[x], d_max);
		}
	}
	int l, r;
	for (l = q; f[l] < dis[l]; l = pre[l]);
	for (r = p; f[r] < dis[q] - dis[r]; r = nxt[r]);
	int cnt = 0;
	for (int x = l; x != r; x = nxt[x]) cnt++;
	printf("%d\n", cnt);
	return 0;
}