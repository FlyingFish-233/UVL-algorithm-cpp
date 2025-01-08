// POJ1679 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge &cmp) const {
        return w < cmp.w;
    }
};

int n, m;
Edge g[NR];
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

int kruskal()
{
    sort(g + 1, g + m + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    int ans = 0, s1 = 0, s2 = 0; g[0].w = g[m + 1].w = 2e9;
    for (int i = 1; i <= m + 1; i++) {
        if (g[i].w != g[i - 1].w) {
            if (s1 != s2) return -1;
            s1 = s2 = 0;
            for (int j = i; j <= m && g[j].w == g[i].w; j++)
                if (find(g[j].u) != find(g[j].v)) s1++;
        }
        if (i > m) break;
        int x = find(g[i].u), y = find(g[i].v);
        if (x != y) ans += g[i].w, merge(x, y), s2++;
    }
    return ans;
}

/*
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
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (flag[j] && g[x][j] == dis[x]) cnt++;
        if (cnt > 1) return -1;
        flag[x] = true, ans += dis[x];
        for (int y = 1; y <= n; y++)
            if (!flag[y]) dis[y] = min(dis[y], g[x][y]);
    }
    return ans;
}
*/

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
        int ans = kruskal();
        if (ans == -1) printf("Not Unique!\n");
        else printf("%d\n", ans);
    }
    return 0;
}