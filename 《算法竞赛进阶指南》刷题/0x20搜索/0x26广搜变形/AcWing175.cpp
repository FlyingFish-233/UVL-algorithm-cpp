# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 3e5 + 10, MR = 2e6 + 10;

struct Edge
{
	int to, next, w;
};

int n, m;
char c[510][510];

int gsz, fte[NR];
Edge g[MR];

int dis[NR];
deque<int> q;

int id(int x, int y)
{
	return x * (m + 1) + y;
}

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", c[i]);
		gsz = 0;
		memset(fte, 0, sizeof(fte));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				int w1 = 1, w2 = 1;
				if (c[i][j] == '\\') w1 = 0;
				if (c[i][j] == '/') w2 = 0;
				addEdge(id(i, j), id(i + 1, j + 1), w1);
				addEdge(id(i + 1, j), id(i, j + 1), w2);
			}
		memset(dis, 0x3f, sizeof(dis));
		dis[0] = 0;
		q.push_back(0);
		while (!q.empty()) {
			int x = q.front();
			q.pop_front();
			for (int i = fte[x]; i; i = g[i].next) {
				int y = g[i].to;
				if (dis[y] <= dis[x] + g[i].w) continue;
				dis[y] = dis[x] + g[i].w;
				if (g[i].w == 0) q.push_front(y);
				else q.push_back(y);
			}
		}
		if (dis[id(n, m)] > 1e9) printf("NO SOLUTION\n");
		else printf("%d\n", dis[id(n, m)]);
	}
	return 0;
}