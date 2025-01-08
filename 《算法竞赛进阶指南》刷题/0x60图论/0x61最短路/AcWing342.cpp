# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <vector>

using namespace std;

const int NR = 3e4 + 10, MR = 2e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, m1, m2, s;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

int tot, c[NR];
vector<int> v[NR];

void dfs(int x)
{
	c[x] = tot;
	for (int i = fte[x]; i; i = g[i].next)
		if (c[g[i].to] == 0) dfs(g[i].to);
}

int in[NR];
queue<int> q;

struct Node
{
	int x, d;
	bool operator < (const Node &cmp) const {
		return d > cmp.d;
	}
};

int dis[NR];
priority_queue<Node> h;
bool flag[NR];

int main()
{
	scanf("%d%d%d%d", &n, &m1, &m2, &s);
	for (int i = 1; i <= m1; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		addEdge(x, y, w);
		addEdge(y, x, w);
	}
	for (int i = 1; i <= n; i++)
		if (c[i] == 0) tot++, dfs(i);
	for (int i = 1; i <= n; i++)
		v[c[i]].push_back(i);

	for (int i = 1; i <= m2; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		addEdge(x, y, w), in[c[y]]++;
	}
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	for (int i = 1; i <= tot; i++)
		if (in[i] == 0) q.push(i);
	while (!q.empty()) {
		int col = q.front(); q.pop();
		for (int i = 0; i < (int) v[col].size(); i++)
			h.push((Node) {v[col][i], dis[v[col][i]]});
		while (!h.empty()) {
			int x = h.top().x; h.pop();
			if (flag[x]) continue;
			flag[x] = true;
			for (int i = fte[x]; i; i = g[i].next) {
				int y = g[i].to;
				if (c[x] != c[y] && --in[c[y]] == 0) q.push(c[y]);
				if (dis[y] <= dis[x] + g[i].w) continue;
				dis[y] = dis[x] + g[i].w;
				if (c[x] == c[y]) h.push((Node) {y, dis[y]});
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (dis[i] < 1e9) printf("%d\n", dis[i]);
		else printf("NO PATH\n");
	return 0;
}