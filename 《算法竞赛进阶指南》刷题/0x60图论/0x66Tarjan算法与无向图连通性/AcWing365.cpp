# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
bool hate[NR][NR];
vector<int> g[NR];

int now, dfn[NR], low[NR];
int top, st[NR];

int root, tot;
vector<int> dcc[NR];
bool cut[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now, st[++top] = x;
    if (x == root && g[x].size() == 0) { dcc[++tot].push_back(x); return; }
    int tmp = 0;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i], z;
        if (dfn[y] != 0) { low[x] = min(low[x], dfn[y]); continue; }
        tarjan(y), low[x] = min(low[x], low[y]);
        if (dfn[x] <= low[y]) {
            tmp++;
            if (x != root || tmp > 1) cut[x] = true;
            dcc[++tot].push_back(x);
            do {
                z = st[top--];
                dcc[tot].push_back(z);
            } while (z != y);
        }
    }
}

int c[NR];
bool flag[NR], ans[NR];

bool check(int x, int color)
{
    c[x] = color;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (!flag[y] || c[y] == 3 - color) continue;
        if (c[y] == color) return false;
        if (c[y] == 0 && !check(y, 3 - color)) return false;
    }
    return true;
}

int main()
{
    while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
        memset(hate, false, sizeof(hate));
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), hate[x][y] = hate[y][x] = true;

        for (int i = 1; i <= n; i++)
            g[i].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && !hate[i][j]) g[i].push_back(j);

        memset(dfn, 0, sizeof(dfn)), now = 0;
        memset(cut, false, sizeof(cut)), tot = 0;
        for (int i = 1; i <= n; i++)
            dcc[i].clear();
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0) tarjan(root = i);
        memset(ans, false, sizeof(ans));
        for (int i = 1; i <= tot; i++) {
            memset(flag, false, sizeof(flag));
            memset(c, 0, sizeof(c));
            for (int j = 0; j < (int) dcc[i].size(); j++)
                flag[dcc[i][j]] = true;
            if (check(dcc[i][0], 1)) continue;
            for (int j = 0; j < (int) dcc[i].size(); j++)
                ans[dcc[i][j]] = true;
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            cnt += ans[i];
        printf("%d\n", n - cnt);
    }
    return 0;
}