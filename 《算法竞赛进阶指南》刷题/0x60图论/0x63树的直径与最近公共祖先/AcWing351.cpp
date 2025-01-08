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

int doit(int s)
{
	int res = 0, l = 1, r = 0;
	q[++r] = s;
	while (l <= r) {
		int x = q[l++];
		res = max(res, dis[x]);
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dis[y] == INF)
				dis[y] = dis[x] + g[i].w, q[++r] = y;
		}
	}
	return res;
}

bool check(int mid)
{
	int u = 0, v = path.size() - 1;
	while (u + 1 < (int) path.size() && path[u + 1].second <= mid) u++;
	while (v - 1 >= 0 && path.back().second - path[v - 1].second <= mid) v--;
	if (u > v) return true;
	if (path[v].second - path[u].second > S) return false;
	memset(dis, 0x3f, sizeof(dis));
	for (auto p : path) dis[p.first] = 0;
	for (int i = u; i <= v; i++)
		if (doit(path[i].first) > mid) return false;
	return true;
}

int main()
{
	scanf("%d%d", &n, &S);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
	int u = bfs(1), v = bfs(u);
	for (int x = v; x; x = pre[x])
		path.push_back({x, dis[x]});
	reverse(path.begin(), path.end());
	int l = 0, r = 2e9, ans;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}