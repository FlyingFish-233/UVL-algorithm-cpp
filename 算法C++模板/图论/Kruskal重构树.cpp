// P4768 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 6e5 + 10;

struct Edge
{
	int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

struct Node
{
    int x, d;
    bool operator < (const Node &cmp) const {
        return d > cmp.d;
    }
};

int dis[NR];
priority_queue<Node> q;
bool flag[NR];

void heap_dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(flag, false, sizeof(flag));
    q.push((Node) {s, dis[s] = 0});
    while (!q.empty()) {
        int x = q.top().x; q.pop();
        if (flag[x]) continue;
        flag[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] > dis[x] + g[i].w)
                q.push((Node) {y, dis[y] = dis[x] + g[i].w});
        }
    }
}

struct Array
{
	int u, v, w;
	bool operator < (const Array &cmp) const {
		return w > cmp.w;
	}
};

int tmp[NR];
Array e[NR];

int find(int x)
{
	if (tmp[x] == x) return x;
	return tmp[x] = find(tmp[x]);
}

int root;
int fa[NR][21], dep[NR];

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y != dad) build(y, x), dis[x] = min(dis[x], dis[y]);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(fte, 0, sizeof(fte)), gsz = 0;
		for (int i = 1, l; i <= m; i++) {
			scanf("%d%d%d%d", &e[i].u, &e[i].v, &l, &e[i].w);
			addEdge(e[i].u, e[i].v, l);
		}
		heap_dijkstra(1);

		memset(fte, 0, sizeof(fte)), gsz = 0;
		sort(e + 1, e + m + 1);
		for (int i = 1; i <= n + m; i++) tmp[i] = i;
		for (int i = 1; i <= m; i++) {
			int x = find(e[i].u), y = find(e[i].v);
			if (x != y) addEdge(n + i, x, 0), addEdge(n + i, y, 0), root = tmp[x] = tmp[y] = n + i;
		}
		memset(fa, 0, sizeof(fa));
		dep[0] = 1, build(root, 0);

		int Q, K, S, lastans = 0;
		scanf("%d%d%d", &Q, &K, &S);
		while (Q--) {
			int x, p;
			scanf("%d%d", &x, &p);
			x = (x + lastans * K - 1) % n + 1;
			p = (p + lastans * K) % (S + 1);
			for (int i = 20; i >= 0; i--)
				if (fa[x][i] != 0 && e[fa[x][i] - n].w > p) x = fa[x][i];
			printf("%d\n", lastans = dis[x]);
		}
	}
	return 0;
}