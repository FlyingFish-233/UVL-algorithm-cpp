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

int n, m, k;
int u[MR], v[MR], w[MR];

int gsz, fte[NR];
Edge g[MR << 1];

int dis[NR];
deque<int> q;

void addEdge(int x, int y, int z)
{
	g[++gsz] = (Edge) {y, fte[x], z};
	fte[x] = gsz;
}

bool check(int mid)
{
	gsz = 0;
	memset(fte, 0, sizeof(fte));
	for (int i = 1; i <= m; i++)
		addEdge(u[i], v[i], w[i] > mid), addEdge(v[i], u[i], w[i] > mid);
	memset(dis, 0x3f, sizeof(dis));
	q.push_back(1), dis[1] = 0;
	while (!q.empty()) {
		int x = q.front(); q.pop_front();
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dis[y] <= dis[x] + g[i].w) continue;
			dis[y] = dis[x] + g[i].w;
			if (g[i].w == 0) q.push_front(y);
			if (g[i].w == 1) q.push_back(y);
		}
	}
	return dis[n] <= k;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &u[i], &v[i], &w[i]);
	int l = 0, r = 1e6, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}