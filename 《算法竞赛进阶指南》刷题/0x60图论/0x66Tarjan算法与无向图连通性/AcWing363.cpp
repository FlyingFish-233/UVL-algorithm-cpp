# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
vector<int> g[NR];

int now, dfn[NR], low[NR], sz[NR];
bool cut[NR];
long long ans[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now, sz[x] = 1;
    int tmp = 0, sum = 0;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (dfn[y] != 0) { low[x] = min(low[x], dfn[y]); continue; }
        tarjan(y), low[x] = min(low[x], low[y]);
        sz[x] += sz[y];
        if (dfn[x] <= low[y]) {
            tmp++;
            ans[x] += 1ll * sz[y] * (n - sz[y]);
            sum += sz[y];
            if (x != 1 || tmp > 1) cut[x] = true;
        }
    }
    if (cut[x]) ans[x] += 1ll * (n - sum - 1) * (sum + 1) + (n - 1);
    else ans[x] = 2 * (n - 1);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    tarjan(1);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
    return 0;
}