# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <stack>

using namespace std;

const int NR = 100, MR = 2e3 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, s, t;
int x_min[NR], x_max[NR], y_min[NR], y_max[NR];
int gsz = 1, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], 0}, fte[y] = gsz;
}

int dep[NR], head[NR];
queue <int> q;

bool bfs()
{
	while (!q.empty()) q.pop();
	memset(dep, 0, sizeof(dep));
	memcpy(head, fte, sizeof(fte));
	dep[s] = 1,	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = fte[x]; i; i = g[i].next) {
			int y = g[i].to;
			if (dep[y] != 0 || g[i].w == 0) continue;
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
		if (dep[y] != dep[x] + 1 || g[i].w == 0) continue;
		int delta = dfs(y, min(lim - flow, g[i].w));
		if (delta == 0) dep[y] = 0;
		else g[i].w -= delta, g[i ^ 1].w += delta, flow += delta;
		head[x] = i;
	}
	return flow;
}

int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> st;
int tot, c[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now;
    ins[x] = true, st.push(x);
    for (int i = fte[x]; i; i = g[i].next) if (g[i].w != 0) {
        int y = g[i].to;
        if (dfn[y] == 0) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    c[x] = ++tot;
    while (st.top() != x)
        c[st.top()] = tot, ins[st.top()] = false, st.pop();
    ins[x] = false, st.pop();
}

pair<int, int> ans[MR];

int main()
{
	for (int save = 1; scanf("%d", &n) && n; save++) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d%d", &x_min[i], &x_max[i], &y_min[i], &y_max[i]);
		s = 0, t = 2 * n + 1, m = 0;
		memset(fte, 0, sizeof(fte)), gsz = 1;
		for (int i = 1, x, y; i <= n; i++) {
			scanf("%d%d", &x, &y);
			for (int j = 1; j <= n; j++)
				if (x_min[j] <= x && x <= x_max[j] && y_min[j] <= y && y <= y_max[j])
					addEdge(i, j + n, 1), ++m;
		}
		for (int i = 1; i <= n; i++) addEdge(s, i, 1);
		for (int i = 1; i <= n; i++) addEdge(i + n, t, 1);
		while (bfs()) dfs(s, 2e9);
		memset(dfn, 0, sizeof(dfn)), now = tot = 0;
		for (int i = s; i <= t; i++)
			if (dfn[i] == 0) tarjan(i);
		int cnt = 0;
		for (int i = 2; i <= 2 * m + 1; i += 2) {
			int x = g[i ^ 1].to, y = g[i].to;
			if (g[i].w == 0 && c[x] != c[y]) ans[++cnt] = {y - n, x};
		}
		printf("Heap %d\n", save);
		if (cnt == 0) { printf("none\n\n"); continue; }
		sort(ans + 1, ans + cnt + 1);
		for (int i = 1; i <= cnt; i++)
			printf("(%c,%d) ", ans[i].first + 'A' - 1, ans[i].second);
		printf("\n\n");
	}
	return 0;
}