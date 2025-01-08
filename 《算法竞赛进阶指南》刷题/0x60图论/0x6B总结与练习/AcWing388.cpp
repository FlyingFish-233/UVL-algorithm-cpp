# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20, MR = (1 << 16) + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge &cmp) const {
        return w < cmp.w;
    }
};

int n, m, lim;
int a[NR];
Edge g[NR * NR];

int sum[MR], f[MR];

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

int kruskal(int sta)
{
    sort(g + 1, g + m + 1);
    int ans = 0, cnt = 0, all = 0;
    for (int i = 0; i < n; i++)
        fa[i] = i, all += (sta >> i & 1);
    for (int i = 1; i <= m; i++) if ((sta >> g[i].u & 1) && (sta >> g[i].v & 1)) {
        int x = find(g[i].u), y = find(g[i].v);
        if (x != y) ans += g[i].w, merge(x, y), cnt++;
    }
    if (cnt < all - 1) return INF;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m), lim = (1 << n) - 1;
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
    memset(f, 0x3f, sizeof(f));
    for (int sta = 0; sta <= lim; sta++) {
        for (int i = 0; i < n; i++)
            if (sta >> i & 1) sum[sta] += a[i];
        if (sum[sta] == 0) f[sta] = kruskal(sta);
    }
    for (int sta = 0; sta <= lim; sta++) if (sum[sta] == 0)
        for (int sta0 = sta; sta0 != 0; sta0 = (sta0 - 1) & sta) if (sum[sta0] == 0)
            f[sta] = min(f[sta], f[sta0] + f[sta - sta0]);
    if (f[lim] == INF) printf("Impossible\n");
    else printf("%d\n", f[lim]);
    return 0;
}