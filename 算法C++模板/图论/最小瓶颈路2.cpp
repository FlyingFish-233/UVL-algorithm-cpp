// LOJ137 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10, mod = 1e9 + 7;

struct Edge
{
	int to, next;
};

int n, m;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y)
{
	g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz;
}

struct Array
{
	int u, v, w;
	bool operator < (const Array &cmp) const {
		return w < cmp.w;
	}
};

Array e[NR];
int tmp[NR];

int find(int x)
{
	if (tmp[x] == x) return x;
	return tmp[x] = find(tmp[x]);
}

int root, dep[NR];
int tot, dfn[NR];
int lg2[NR << 1], pos[NR << 1][30];

void build(int x, int dad)
{
	pos[++tot][0] = x, dfn[x] = tot;
	dep[x] = dep[dad] + 1;
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y != dad) build(y, x), pos[++tot][0] = x;
	}
}

void init()
{
	for (int i = 2; i <= tot; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int j = 1; (1 << j) <= tot; j++)
		for (int i = 1; i + (1 << j) - 1 <= tot; i++) {
			int x = pos[i][j - 1], y = pos[i + (1 << (j - 1))][j - 1];
			pos[i][j] = (dep[x] < dep[y]) ? x : y;
		}
}

int query(int l, int r)
{
	if (l > r) swap(l, r);
	int k = lg2[r - l + 1], x = pos[l][k], y = pos[r - (1 << k) + 1][k];
	return (dep[x] < dep[y]) ? x : y;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n + m; i++) tmp[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) addEdge(n + i, x), addEdge(n + i, y), root = tmp[x] = tmp[y] = n + i;
	}
	build(root, 0), init();
	int T, A, B, C, P, ans = 0;
	scanf("%d%d%d%d%d", &T, &A, &B, &C, &P);
	while (T--) {
		A = (A * B + C) % P; int x = A % n + 1;
		A = (A * B + C) % P; int y = A % n + 1;
		if (x != y) (ans += e[query(dfn[x], dfn[y]) - n].w) %= mod;
	}
	printf("%d\n", ans);
	return 0;
}