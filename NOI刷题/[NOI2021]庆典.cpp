// P7737 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>
# include <queue>

using namespace std;

const int NR = 3e5 + 10;

int n, m, q, k;
vector<int> g[NR];

int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> st;
int tot, c[NR], sz[NR];

void tarjan(int x)
{
	dfn[x] = low[x] = ++now;
	st.push(x), ins[x] = true;
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (dfn[y] == 0) tarjan(y), low[x] = min(low[x], low[y]);
		else if (ins[y]) low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] != low[x]) return;
	c[x] = ++tot, sz[tot] = 1;
	while (st.top() != x) {
		int y = st.top(); st.pop();
		c[y] = tot, sz[tot]++, ins[y] = false;
	}
	st.pop(), ins[x] = false;
}

int in[NR], root;
vector<int> g2[NR], g3[NR];

// 缩点后, 每个点只保留入边中拓扑序最大的边, 不会影响图的连通性
void topSort()
{
	queue<int> q;
	for (int i = 1; i <= tot; i++)
		if (in[i] == 0) root = i, q.push(i);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = 0; i < (int) g2[x].size(); i++) {
			int y = g2[x][i];
			if (--in[y] == 0) g3[x].push_back(y), q.push(y);
		}
	}
}

int cur, hd[NR], tl[NR];
int dep[NR], fa[NR][30], dsum[NR];

void build(int x, int dad)
{
	hd[x] = ++cur;
	fa[x][0] = dad;
	dep[x] = dep[dad] + 1;
	dsum[x] = dsum[dad] + sz[x];
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < (int) g3[x].size(); i++)
		build(g3[x][i], x);
	tl[x] = cur;
}

int lca(int x, int y)
{
	if (dep[x] > dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (dep[fa[y][i]] >= dep[x]) y = fa[y][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i--)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

vector<int> v1, v2;
// v1记录的是从起点走可以到达的所有互不包含的子树
// v2记录的是(在反图上)从终点走可以到达的所有到根的链

// 返回y是否在x的子树当中
bool intree(int x, int y)
{
	return hd[x] <= hd[y] && hd[y] <= tl[x];
}

void addEdge(int x, int y)
{
	bool flag = false;
	for (int i = 0; i < (int) v1.size(); i++)
		if (intree(v1[i], x)) { flag = true; break; }
	for (int i = 0; i < (int) v1.size(); i++)
		if (intree(v1[i], y)) { flag = false; break; }
	if (flag) {
		for (int i = 0; i < (int) v1.size(); i++)
			if (intree(y, v1[i])) v1.erase(v1.begin() + i), i--;
		v1.push_back(y);
	}
	flag = false;
	for (int i = 0; i < (int) v2.size(); i++)
		if (intree(y, v2[i])) { flag = true; break; }
	for (int i = 0; i < (int) v2.size(); i++)
		if (intree(x, v2[i])) { flag = false; break; }
	if (flag) {
		for (int i = 0; i < (int) v2.size(); i++)
			if (intree(v2[i], x)) v2.erase(v2.begin() + i), i--;
		v2.push_back(x);
	}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &q, &k);
	for (int i = 1, x, y; i <= m; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y);
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0) tarjan(i);
	for (int x = 1; x <= n; x++)
		for (int i = 0; i < (int) g[x].size(); i++) {
			int y = g[x][i];
			if (c[x] != c[y]) g2[c[x]].push_back(c[y]), in[c[y]]++;
		}
	topSort(), build(root, 0);
	while (q--) {
		int x, y, x1, y1, x2, y2;
		v1.clear(), v2.clear();
		scanf("%d%d", &x, &y), v1.push_back(c[x]), v2.push_back(c[y]);
		if (k >= 1) scanf("%d%d", &x1, &y1), addEdge(c[x1], c[y1]);
		if (k >= 2) scanf("%d%d", &x2, &y2), addEdge(c[x2], c[y2]), addEdge(c[x1], c[y1]);
		// 有可能加了(c[x2], c[y2])边后, (c[x1], c[y1])才可以到达
		int ans = 0;
		for (int i = 0; i < (int) v1.size(); i++)
			for (int j = 0; j < (int) v2.size(); j++)
				if (intree(v1[i], v2[j])) {
					int tmp = fa[v1[i]][0]; // 有可能v2[l]->v1[i]和v2[j]->v1[i]有重合部分
					for (int l = 0; l < j; l++)
						if (dep[lca(v2[l], v2[j])] > dep[tmp]) tmp = lca(v2[l], v2[j]);
					ans += dsum[v2[j]] - dsum[tmp];
				}
		printf("%d\n", ans);
	}
	return 0;
}
