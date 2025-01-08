// P2805 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 600 + 10, MR = 4e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, s, t;
int a[NR], in[NR];
vector<int> g0[NR];
bool vis[NR];

int gsz = 1, fte[NR];
Edge g[MR << 1];

int dep[NR], head[NR];
queue <int> q;

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], 0}, fte[y] = gsz;
}

void topSort()
{
	for (int x = 0; x < n * m; x++)
		for (int i = 0; i < (int) g0[x].size(); i++)
			in[g0[x][i]]++;
	for (int i = 0; i < n * m; i++)
		if (in[i] == 0) q.push(i), vis[i] = true;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < (int) g0[x].size(); i++) {
			int y = g0[x][i];
			if (!vis[y] && --in[y] == 0) q.push(y), vis[y] = true;
		}
	}
}

bool bfs()
{
	while (!q.empty()) q.pop();
	memcpy(head, fte, sizeof(fte));
	memset(dep, 0, sizeof(dep));
	dep[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (g[i].w == 0 || dep[y]) continue;
			dep[y] = dep[x] + 1;
			q.push(y);
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
		if (g[i].w == 0 || dep[y] != dep[x] + 1) continue;
		int delta = dfs(y, min(lim - flow, g[i].w));
		if (delta == 0) dep[y] = 0;
		else g[i].w -= delta, g[i ^ 1].w += delta, flow += delta;
	}
	return flow;
}

/*
val>=0的点与s连一条边权为val的边
val<0的点与t连一条边权为-val的边 [做最小割]
记A = Sum{与s相连且未被割去的边权}, B = Sum{与s相连且被割去的边权}
记C = Sum{与t相连且未被割去的边权}, D = Sum{与t相连且被割去的边权}

割 = B + D
闭合子图权值 = A - D = (A + B) - 割
最大权闭合子图 = Sum{与s相连的边权} - 最小割
*/
int main()
{
	scanf("%d%d", &n, &m);
	s = n * m, t = s + 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			scanf("%d", &a[i * m + j]);
			int num;
			scanf("%d", &num);
			for (int k = 1; k <= num; k++) {
				int x, y;
				scanf("%d%d", &x, &y);
				g0[i * m + j].push_back(x * m + y);
			}
			if (j < m - 1) g0[i * m + j + 1].push_back(i * m + j);
		}
	topSort();
	int sum = 0;
	for (int i = 0; i < n * m; i++) {
		if (!vis[i]) continue;
		if (a[i] >= 0) addEdge(s, i, a[i]), sum += a[i];
		else addEdge(i, t, -a[i]);
		for (int j = 0; j < (int) g0[i].size(); j++)
			if (vis[g0[i][j]]) addEdge(g0[i][j], i, 2e9);
	}
	int ans = 0;
	while (bfs()) ans += dfs(s, 2e9);
	printf("%d\n", sum - ans);
	return 0;
}