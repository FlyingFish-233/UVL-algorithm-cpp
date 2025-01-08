# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e5 + 10, lim = 5e4 + 1;

struct Edge
{
    int to, next, w;
};

int n;
int gsz, fte[NR];
Edge g[NR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

queue<int> q;
bool already[NR];
int dis[NR];

int spfa(int s)
{
    memset(dis, -0x3f, sizeof(dis));
    dis[s] = 0, already[s] = true, q.push(s);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] >= dis[x] + g[i].w) continue;
            dis[y] = dis[x] + g[i].w;
            if (!already[y]) already[y] = true, q.push(y);
        }
    }
    return dis[lim];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, a, b, c; i <= n; i++)
        scanf("%d%d%d", &a, &b, &c), addEdge((++a) - 1, (++b), c);
    for (int i = 0; i < lim; i++)
        addEdge(i, i + 1, 0), addEdge(i + 1, i, -1);
    printf("%d\n", spfa(1));
    return 0;
}