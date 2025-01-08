# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e6 + 10, MR = 1e7 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int to, next, w;
};

int n, m, k;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

int dis[NR];
queue<int> q;
bool already[NR];

void spfa(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    q.push(s), already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] <= max(dis[x], g[i].w)) continue;
            dis[y] = max(dis[x], g[i].w);
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, x, y, w; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        addEdge(x, y, w), addEdge(y, x, w);
        for (int j = 1; j <= k; j++) {
        	addEdge(x + (j - 1) * n, y + j * n, 0);
        	addEdge(y + (j - 1) * n, x + j * n, 0);
        	addEdge(x + j * n, y + j * n, w);
        	addEdge(y + j * n, x + j * n, w);
        }
    }
    for (int i = 1; i <= k; i++)
    	addEdge(n + (i - 1) * n, n + i * n, 0);
    spfa(1);
    printf("%d\n", (dis[n + k * n] == INF) ? -1 : dis[n + k * n]);
    return 0;
}