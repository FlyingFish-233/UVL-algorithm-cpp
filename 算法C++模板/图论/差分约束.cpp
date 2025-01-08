// P5960 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e4 + 10, MR = 5e5 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

queue<int> q;
int dis[NR], len[NR];
bool already[NR];

bool spfa(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    q.push(s), already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] <= dis[x] + g[i].w) continue;
            dis[y] = dis[x] + g[i].w, len[y] = len[x] + 1;
            if (len[y] >= n + 1) return false;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &y, &x, &w), addEdge(x, y, w);
    for (int i = 1; i <= n; i++)
        addEdge(0, i, 0);
    if (!spfa(0)) return printf("NO\n"), 0;
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]); 
    puts("");
    return 0;
}