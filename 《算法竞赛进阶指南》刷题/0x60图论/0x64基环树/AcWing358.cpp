# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e6 + 10;

struct Edge
{
    int to, next, w;
};

int n;
int to[NR], w[NR];
int gsz, fte[NR], deg[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz, deg[x]++;
    g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz, deg[y]++;
}

int tot, c[NR];
vector<int> block;

void color(int x)
{
    c[x] = tot, block.push_back(x);
    for (int i = fte[x]; i; i = g[i].next)
        if (c[g[i].to] == 0) color(g[i].to);
}

int q[NR];
bool vis[NR];
int len, loop[NR];

void get_loop()
{
    int l = 1, r = 0;
    for (int i = 0; i < (int) block.size(); i++)
        if (deg[block[i]] == 1) q[++r] = block[i];
    while (l <= r) {
        int x = q[l++];
        vis[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (!vis[y] && --deg[y] == 1) q[++r] = y;
        }
    }
    int x; len = 0;
    for (int i = 0; i < (int) block.size(); i++)
        if (!vis[block[i]]) { x = block[i]; break; }
    loop[++len] = x;
    for (int i = to[x]; i != x; i = to[i])
        loop[++len] = i;
}

long long now_max;
long long d[NR];

void dfs(int x, int fa)
{
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y == fa || !vis[y]) continue;
        dfs(y, x);
        now_max = max(now_max, d[x] + d[y] + g[i].w);
        d[x] = max(d[x], d[y] + g[i].w);
    }
}

long long v[NR << 1], s[NR << 1];

void solve()
{
    for (int i = 1; i <= len; i++)
        v[i] = d[loop[i]], s[i] = w[loop[i - 1]];
    s[1] = w[loop[len]];
    for (int i = 1; i <= len; i++)
        v[i + len] = v[i], s[i + len] = s[i];
    for (int i = 1; i <= 2 * len; i++)
        s[i] += s[i - 1];
    int l = 1, r = 0;
    for (int i = 1; i <= 2 * len; i++) {
        while (l <= r && i - q[l] >= len) l++;
        if (l <= r) now_max = max(now_max, v[i] + v[q[l]] + s[i] - s[q[l]]);
        while (l <= r && v[q[r]] - s[q[r]] <= v[i] - s[i]) r--;
        q[++r] = i;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &to[i], &w[i]);
        addEdge(i, to[i], w[i]);
    }
    long long ans = 0;
    for (int x = 1; x <= n; x++) if (c[x] == 0) {
        block.clear(), ++tot, color(x);
        get_loop(), now_max = 0;
        for (int i = 1; i <= len; i++) dfs(loop[i], 0);
        solve(), ans += now_max;
    }
    printf("%lld\n", ans);
    return 0;
}