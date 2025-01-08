// P3366 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int g[NR][NR], dis[NR];
bool flag[NR];

int prim()
{
    memset(dis, 0x3f, sizeof(dis)), dis[1] = 0;
    memset(flag, false, sizeof(flag));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = 0;
        for (int j = 1; j <= n; j++)
            if (!flag[j] && (x == 0 || dis[j] < dis[x])) x = j;
        if (dis[x] == INF) return -1;
        flag[x] = true, ans += dis[x];
        for (int y = 1; y <= n; y++)
            if (!flag[y]) dis[y] = min(dis[y], g[x][y]);
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; i++) g[i][i] = 0;
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), g[x][y] = g[y][x] = min(g[x][y], w);
    int ans = prim();
    if (ans == -1) printf("orz\n");
    else printf("%d\n", ans);
    return 0;
}