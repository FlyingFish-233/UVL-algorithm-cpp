// AcWing849 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 500 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int g[NR][NR], dis[NR];
bool flag[NR];

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    for (int i = 1; i <= n - 1; i++) {
        int x = 0;
        for (int j = 1; j <= n; j++)
            if (!flag[j] && (x == 0 || dis[j] < dis[x])) x = j;
        flag[x] = true;
        for (int y = 1; y <= n; y++)
            if (!flag[y]) dis[y] = min(dis[y], dis[x] + g[x][y]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; i++) g[i][i] = 0;
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), g[x][y] = min(g[x][y], w);
    dijkstra(1);
    printf("%d\n", (dis[n] == INF) ? -1 : dis[n]);
    return 0;
}