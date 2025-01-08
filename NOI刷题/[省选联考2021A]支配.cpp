// P7520 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 3000 + 10;

int n, m, T;
vector<int> g[NR], g0[NR];

bool vis[NR][NR]; // vis[i][ban]表示删除ban后, 1能否到达i
vector<int> o[NR]; // 受支配集
int fa[NR]; // 支配树

void dfs(int x, int ban)
{
    if (x == ban) return;
    vis[x][ban] = true;
    for (int i = 0; i < (int) g[x].size(); i++)
        if (!vis[g[x][i]][ban]) dfs(g[x][i], ban);
}

bool vis0[NR][NR]; // vis0[i][ban]表示删除fa[ban]后, ban能否到达i

void dfs0(int x, int ban)
{
    if (x == fa[ban]) return;
    vis0[x][ban] = true;
    for (int i = 0; i < (int) g0[x].size(); i++)
        if (!vis0[g0[x][i]][ban]) dfs0(g0[x][i], ban);
}

vector<int> G[NR]; // 支配树
bool change[NR];

void down(int x)
{
    for (int i = 0; i < (int) G[x].size(); i++)
        change[G[x][i]] |= change[x], down(G[x][i]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y), g0[y].push_back(x);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        dfs(1, i);
        for (int j = 1; j <= n; j++)
            if (vis[j][0] && !vis[j][i]) o[j].push_back(i);
    }
    for (int x = 1; x <= n; x++)
        for (int i = 0; i < (int) o[x].size(); i++)
            if (o[o[x][i]].size() == o[x].size() - 1) {
                fa[x] = o[x][i];
                G[o[x][i]].push_back(x);
                break;
            }
    for (int i = 2; i <= n; i++)
        dfs0(i, i);
    while (T--) {
        int p, q, ans = 0;
        scanf("%d%d", &p, &q);
        for (int i = 2; i <= n; i++)
            change[i] = (fa[i] != 1 && fa[i] != p && fa[i] != q && vis[p][fa[i]] & vis0[q][i]);
        down(1);
        for (int i = 1; i <= n; i++)
            ans += change[i];
        printf("%d\n", ans);
    }
    return 0;
}

