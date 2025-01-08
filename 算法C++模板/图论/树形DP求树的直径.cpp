# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int to, next, w;
};

int n;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w};
	fte[x] = gsz;
}

int len, dis[NR];

void dfs(int x, int fa)
{
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y == fa) continue;
		dfs(y, x);
		len = max(len, dis[x] + dis[y] + g[i].w);
		dis[x] = max(dis[x], dis[y] + g[i].w);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, x, y, w; i <= n - 1; i++)
		scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w), addEdge(y, x, w);
	memset(dis, 0, sizeof(dis));
	dfs(1, 0);
	printf("%d\n", len);
	return 0;
}