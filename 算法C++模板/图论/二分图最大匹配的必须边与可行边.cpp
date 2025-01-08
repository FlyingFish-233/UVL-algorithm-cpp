// AcWing380 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <stack>

using namespace std;

const int NR = 2e4 + 10, MR = 2e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, m, s, t, edge_num;
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

int cnt, ans[MR];

/*
1.若“最大匹配 = 完备匹配”
必须边 <=> (x,y)为匹配边 & 删去(x,y)后不存在x->y的增广路
可行边 <=> (x,y)为匹配边 | 匹配(x,y)后存在x'->y'的增广路 (其中(x,x') (y,y')为匹配边)

[匹配边(x,y)变为y->x, 非匹配边(x,y)变为x->y]
必须边 <=> (x,y)为匹配边 & x与y不互相到达(处于不同SCC)
可行边 <=> (x,y)为匹配边 | x与y能互相到达(处于同一SCC)

2.无条件限制
[先做网络流, 之后只走w[x->y]=1的边求SCC]
必须边 <=> w[x->y] = 0 & x与y处于不同SCC
可行边 <=> w[x->y] = 0 | x与y处于同一SCC
*/
int main()
{
	scanf("%d%d%d", &n, &m, &edge_num);
	s = 0, t = n + m + 1;
	for (int i = 1, x, y; i <= edge_num; i++)
		scanf("%d%d", &x, &y), addEdge(x, y + n, 1);
	for (int i = 1; i <= n; i++) addEdge(s, i, 1);
	for (int i = 1; i <= m; i++) addEdge(i + n, t, 1);
	while (bfs()) dfs(s, 2e9);
	for (int i = s; i <= t; i++)
		if (dfn[i] == 0) tarjan(i);
	for (int i = 2; i <= 2 * edge_num + 1; i += 2) {
		int x = g[i ^ 1].to, y = g[i].to;
		if (g[i].w != 0 && c[x] != c[y]) ans[++cnt] = i >> 1;
	}
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; i++)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}