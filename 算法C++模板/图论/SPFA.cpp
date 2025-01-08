// P3371 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <climits>
# include <queue>

using namespace std;

const int NR = 1e4 + 10, MR = 5e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int to, next, w;
};

int n, m, s0;
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
            if (dis[y] <= dis[x] + g[i].w) continue;
            dis[y] = dis[x] + g[i].w;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &s0);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
    spfa(s0);
    for (int i = 1; i <= n; i++)
        printf("%d ", (dis[i] == INF) ? INT_MAX : dis[i]);
    puts("");
    return 0;
}