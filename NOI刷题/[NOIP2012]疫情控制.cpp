// P1084 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

struct Edge
{
    int to, next, w;
};

int n, m, bsz;
int gsz, fte[NR];
Edge g[NR << 1];
pair<int, int> a[NR], b[NR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

int fa[NR][30], dep[NR], dis[NR], root[NR];

void build(int x, int from)
{
    fa[x][0] = from, dep[x] = dep[from] + 1;
    root[x] = (dep[x] <= 3) ? x : root[from];
    for (int i = 1; (1 << i) <= dep[x]; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y != from) dis[y] = dis[x] + g[i].w, build(y, x);
    }
}

bool vis[NR];
int len, save[NR];

int query(int x, int d)
{
    for (int i = 20; i >= 0; i--)
        if (dis[x] - dis[fa[x][i]] <= d) x = fa[x][i], d -= dis[x] - dis[fa[x][i]];
    return x;
}

void mark(int x)
{
    vis[x] = true;
    if (dep[x] <= 3) return;
    int y = fa[x][0];
    for (int i = fte[y]; i; i = g[i].next)
        if (!vis[g[i].to] && g[i].to != fa[y][0]) return;
    mark(y);
}

bool check(int mid)
{
    memset(vis, false, sizeof(vis)), len = 0;
    for (int i = 1; i <= m; i++) {
        int x = a[i].second;
        if (x == 1) save[++len] = mid;
        else if (mid < dis[x] - dis[root[x]]) mark(query(x, mid));
        else if (mid >= dis[x] + dis[root[x]]) save[++len] = mid - dis[x];
        else if (!vis[root[x]]) mark(root[x]);
        else if (mid > dis[x]) save[++len] = mid - dis[x];
    }
    sort(save + 1, save + len + 1);
    for (int i = 1, j = 1; i <= bsz; i++) {
        if (vis[b[i].second]) continue;
        while (j <= len && save[j] < b[i].first) j++;
        if (j++ > len) return false;
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y, w; i <= n - 1; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
    dep[0] = 1, build(1, 0);
    scanf("%d", &m);
    for (int i = 1, x; i <= m; i++)
        scanf("%d", &x), a[i] = {dis[x] - dis[root[x]], x};
    sort(a + 1, a + m + 1);
    reverse(a + 1, a + m + 1);
    for (int i = fte[1]; i; i = g[i].next)
        b[++bsz] = {g[i].w, g[i].to};
    sort(b + 1, b + bsz + 1);
    int l = 0, r = 1e9, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}