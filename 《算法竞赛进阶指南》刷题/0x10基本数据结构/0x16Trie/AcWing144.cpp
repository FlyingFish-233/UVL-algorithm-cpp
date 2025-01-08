# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10, MR = 31 * 1e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, ans;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

int cnt, trie[MR][2];

void insert(int x)
{
	int now = 0;
	for (int i = 31; i >= 0; i--) {
		int t = x >> i & 1;
		if (trie[now][t] == 0) trie[now][t] = ++cnt;
		now = trie[now][t];
	}
}

int getmax(int now, int x, int k)
{
	if (k < 0) return 0;
	int t = (x >> k) & 1;
	if (trie[now][!t]) return (1 << k) | getmax(trie[now][!t], x, k - 1);
	return getmax(trie[now][t], x, k - 1);
}

void dfs(int x, int fa, int w)
{
	ans = max(ans, getmax(0, w, 31));
	insert(w);
	for (int i = fte[x]; i; i = g[i].next)
		if (g[i].to != fa) dfs(g[i].to, x, w ^ g[i].w);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		addEdge(x, y, w);
		addEdge(y, x, w);
	}
	dfs(1, -1, 0);
	printf("%d\n", ans);
	return 0;
}