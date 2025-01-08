# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e4 + 10, MR = 1e5 + 10;

struct Edge
{
    int to, next;
};

int n, m;
int u[MR], v[MR], w[MR];

int gsz, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz;
}

int c[NR];

bool dfs(int x, int color)
{
    c[x] = color;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (c[y] == 3 - color) continue;
        if (c[y] == color || !dfs(y, 3 - color)) return false;
    }
    return true;
}

bool check(int mid)
{
    memset(fte, 0, sizeof(fte)), gsz = 0;
    for (int i = 1; i <= m; i++)
        if (w[i] > mid) addEdge(u[i], v[i]);
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; i++)
        if (c[i] == 0 && !dfs(i, 1)) return false;
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
    int l = 0, r = 1e9, ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}