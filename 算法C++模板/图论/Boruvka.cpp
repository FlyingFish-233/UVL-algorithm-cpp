// P3366 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10, MR = 2e5 + 10;

struct Edge
{
    int u, v, w;
};

int n, m;
Edge g[MR];

int fa[NR], inw[NR];
bool used[MR];

int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

int Boruvka()
{
    int ans = 0, cnt = 0; g[0].w = 2e9;
    while (true) {
        memset(inw, 0, sizeof(inw));
        for (int i = 1; i <= m; i++) if (!used[i]) {
            int x = find(g[i].u), y = find(g[i].v);
            if (x == y) continue;
            if (g[i].w < g[inw[x]].w) inw[x] = i;
            if (g[i].w < g[inw[y]].w) inw[y] = i;
        }
        bool flag = false;
        for (int i = 1; i <= n; i++) if (inw[i] && !used[inw[i]]) {
            used[inw[i]] = flag = true;
            ans += g[inw[i]].w, cnt++;
            merge(g[inw[i]].u, g[inw[i]].v);
        }
        if (!flag) break;
    }
    if (cnt < n - 1) return -1;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
    int ans = Boruvka();
    if (ans == -1) printf("orz\n");
    else printf("%d\n", ans);
    return 0;
}