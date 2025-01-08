# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

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

int d1[NR], d2[NR];

void dfs1(int x)
{
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        dfs1(y);
        if (d1[x] <= d1[y] + g[i].w) d2[x] = d1[x], d1[x] = d1[y] + g[i].w;
        else if (d2[x] <= d1[y] + g[i].w) d2[x] = d1[y] + g[i].w;
    }
}

int f[NR], ans[NR];

void dfs2(int x)
{
    ans[x] = max(f[x], d1[x]);
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (d1[y] + g[i].w == d1[x]) f[y] = max(f[x], d2[x]) + g[i].w;
        else f[y] = max(f[x], d1[x]) + g[i].w;
        dfs2(y);
    }
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        memset(fte, 0, sizeof(fte)), gsz = 0;
        for (int i = 2, x, w; i <= n; i++)
            scanf("%d%d", &x, &w), addEdge(x, i, w);
        memset(d1, 0, sizeof(d1));
        memset(d2, -0x3f, sizeof(d2));
        memset(f, 0, sizeof(f));
        dfs1(1), dfs2(1);
        for (int i = 1; i <= n; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}