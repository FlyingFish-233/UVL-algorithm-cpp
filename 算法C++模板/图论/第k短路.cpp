// AcWing178 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e3 + 10, MR = 1e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, s, t, k;
int u[MR], v[MR], w[MR];

int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

struct Node
{
	int x, w;

	bool operator < (const Node &cmp) const {
		return w > cmp.w;
	}
};

priority_queue<Node> q;
int f[NR], cnt[NR];

void dijkstra()
{
	memset(f, 0x3f, sizeof(f));
	q.push((Node) {t, f[t] = 0});
	while (!q.empty()) {
		int x = q.top().x;
		q.pop();
		if (cnt[x]) continue;
		cnt[x] = 1;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (f[y] > f[x] + g[i].w && !cnt[y])
				q.push((Node) {y, f[y] = f[x] + g[i].w});
		}
	}
}

int A_star()
{
	if (s == t) k++;
	memset(cnt, 0, sizeof(cnt));
	q.push((Node) {s, f[s]});
	while (!q.empty()) {
		int x = q.top().x, d = q.top().w - f[x];
		q.pop();
		if (cnt[x] > k) continue;
		cnt[x]++;
		if (x == t && cnt[x] == k) return d;
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (cnt[y] <= k)
				q.push((Node) {y, d + g[i].w + f[y]});
		}
	}
	return -1;
}

int main()
{
	scanf("%d%d", &n, &m);
	if (m == 0) {
		printf("-1\n");
		return 0;
	}
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &u[i], &v[i], &w[i]);
	scanf("%d%d%d", &s, &t, &k);
	for (int i = 1; i <= m; i++)
		addEdge(v[i], u[i], w[i]);
	dijkstra();
	gsz = 0;
	memset(fte, 0, sizeof(fte));
	for (int i = 1; i <= m; i++)
		addEdge(u[i], v[i], w[i]);
	printf("%d\n", A_star());
	return 0;
}