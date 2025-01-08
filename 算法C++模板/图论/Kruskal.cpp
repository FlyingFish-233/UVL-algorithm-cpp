// P3366 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10, MR = 2e5 + 10;

struct Edge
{
	int u, v, w;
	bool operator < (const Edge &cmp) const {
		return w < cmp.w;
	}
};

int n, m;
Edge g[MR];
int fa[NR];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	fa[find(x)] = find(y);
}

int kruskal()
{
	sort(g + 1, g + m + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	int ans = 0, cnt = 0;
	for (int i = 1; i <= m; i++) {
		int x = find(g[i].u), y = find(g[i].v);
		if (x != y) ans += g[i].w, merge(x, y), cnt++;
	}
	if (cnt < n - 1) return -1;
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
    int ans = kruskal();
    if (ans == -1) printf("orz\n");
    else printf("%d\n", ans);
	return 0;
}