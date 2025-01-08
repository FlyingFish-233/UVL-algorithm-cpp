// P2619 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10, MR = 1e5 + 10;

struct Edge
{
    int u, v, w, c;
    bool operator < (const Edge &cmp) const {
        if (w != cmp.w) return w < cmp.w;
        return c < cmp.c;
        /*
        问题：在白边权值减k-1时, kruskal选出的白边数量为need-1;在白边权值减k时, kruskal选出的白边数量为need+1
            这样就有可能直接把“f(x)-k*x在x=need处取到最小值”的情况跳过去
        如果上述问题存在, 那么白边权值由减k-1变为减k时, 至少有2条白边代替了MST中2条黑边(设a1代替了b1, a2代替了b2)
        而因为权值相等时我们会优先选择白边
        所以只能是减k-1时w[a1]=w[b1]+1且w[a2]=w[b2]+1;减k时w[a1]=w[b1]且w[a2]=w[b2], a1与a2才会代替b1与b2
        然而这样的话, 减k时就会有2组白边与黑边权值相等
        也就是说f(x)-k*x在x=need-1,x=need和x=need+1处同时取到最小值
        所以取斜率k来计算f(need)仍旧没有问题
        */
    }
};

int n, m, need;
Edge g[MR];

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
    sort(g + 1, g + m + 1);
    for (int i = 0; i < n; i++) fa[i] = i;
    ans = 0, p = 0;
    for (int i = 1; i <= m; i++) {
        int x = find(g[i].u), y = find(g[i].v);
        if (x != y) ans += g[i].w, merge(x, y), p += (g[i].c == 0);
    }
}

bool check(int mid)
{
    for (int i = 1; i <= m; i++)
        if (g[i].c == 0) g[i].w -= mid;
    kruskal();
    for (int i = 1; i <= m; i++)
        if (g[i].c == 0) g[i].w += mid;
    return p >= need;
}

// 设f(x) = 恰选x条白边时的最小生成树
// f(x) - f(x-1) <= f(x+1) - f(x)下凸
// 二分直线斜率k, 当f(x)-k*x在x=need处取到最小值时, 这时的k便是与f(x)切于(need,f(need))的直线的斜率
int main()
{
    scanf("%d%d%d", &n, &m, &need);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &g[i].u, &g[i].v, &g[i].w, &g[i].c);
    int l = -100, r = 100, k = -100;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid - 1, k = mid;
        else l = mid + 1;
    }
    check(k);
    printf("%d\n", ans + k * need);
    return 0;
}