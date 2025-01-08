// P5633 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10, MR = 5e5 + 10;

struct Edge
{
    int u, v, w, c;
    bool operator < (const Edge &cmp) const {
        if (w != cmp.w) return w < cmp.w;
        return c < cmp.c;
    }
};

int n, m, s, k;
int m0, m1;
Edge g[MR], G[2][MR];

int fa[NR];
int ans, p;

int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

void kruskal()
{
    for (int i = 1; i <= n; i++) fa[i] = i;
    ans = 0, p = 0;
    for (int i = 1; i <= m; i++) {
        int x = find(g[i].u), y = find(g[i].v);
        if (x != y) ans += g[i].w, merge(x, y), p += (g[i].c == 0);
    }
}

bool check(int mid)
{
    for (int i = 1; i <= m0; i++)
        G[0][i].w -= mid;
    int t0 = 1, t1 = 1;
    for (int i = 1; i <= m; i++)
        if (t1 > m1 || (t0 <= m0 && G[0][t0] < G[1][t1])) g[i] = G[0][t0++];
        else g[i] = G[1][t1++];
    kruskal();
    for (int i = 1; i <= m0; i++)
        G[0][i].w += mid;
    return p >= k;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &k);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        if (u == s || v == s) G[0][++m0] = (Edge) {u, v, w, 0};
        else G[1][++m1] = (Edge) {u, v, w, 1};
        merge(u, v);
    }
    if (m0 < k) return puts("Impossible"), 0;
    int father = find(1);
    for (int i = 2; i <= n; i++)
        if (find(i) != father) return puts("Impossible"), 0;

    sort(G[0] + 1, G[0] + m0 + 1);
    sort(G[1] + 1, G[1] + m1 + 1);
    int l = -3e4, r = 3e4, save = -3e4;
    check(l);
    if (p > k) return puts("Impossible"), 0;
    check(r);
    if (p < k) return puts("Impossible"), 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid - 1, save = mid;
        else l = mid + 1;
    }
    check(save);
    printf("%d\n", ans + save * k);
    return 0;
}