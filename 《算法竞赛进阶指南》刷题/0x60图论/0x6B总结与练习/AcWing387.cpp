# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 500 + 10, MR = 3e5 + 10;

struct Edge
{
	int u, v; double w;
	bool operator < (const Edge &cmp) const {
		return w < cmp.w;
	}
};

int n, m, k;
int a[NR], b[NR];

double dist(int i, int j)
{
	return sqrt((a[i] - a[j]) * (a[i] - a[j]) + (b[i] - b[j]) * (b[i] - b[j]));
}

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

double kruskal()
{
	sort(g + 1, g + m + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		int x = find(g[i].u), y = find(g[i].v);
		if (x != y) {
			merge(x, y), cnt++;
			if (n - cnt == k) return g[i].w;
		}
	}
	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &k, &n);
   		for (int i = 1; i <= n; i++)
        	scanf("%d%d", &a[i], &b[i]);
        m = 0;
        for (int i = 1; i <= n; i++)
        	for (int j = i + 1; j <= n; j++)
        		g[++m] = (Edge) {i, j, dist(i, j)};
    	printf("%.2f\n", kruskal());
    }
	return 0;
}