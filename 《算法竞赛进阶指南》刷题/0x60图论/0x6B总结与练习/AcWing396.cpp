# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
vector<int> g[NR];

int now, root;
int dfn[NR], low[NR];
bool cut[NR];

int tot;
stack<int> s;
vector<int> dcc[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now, s.push(x);
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
                z = s.top(), s.pop();
                dcc[tot].push_back(z);
            } while (z != y);
        }
    }
}

int main()
{
    for (int c = 1; scanf("%d", &m) && m; c++) {
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i <= tot; i++) dcc[i].clear();
        n = tot = 0;
        for (int i = 1, x, y; i <= m; i++) {
            scanf("%d%d", &x, &y);
            g[x].push_back(y);
            g[y].push_back(x);
            n = max(n, max(x, y));
        }
        memset(dfn, 0, sizeof(dfn)), now = 0;
        memset(low, 0, sizeof(low));
        memset(cut, false, sizeof(cut));
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0) tarjan(root = i);
        int ans1 = 0; long long ans2 = 1;
        for (int i = 1; i <= tot; i++) {
            int cnt = 0;
            for (int j = 0; j < (int) dcc[i].size(); j++)
                if (cut[dcc[i][j]]) cnt++;
            if (dcc[i].size() == 1) ans1++;
            else if (cnt == 0) ans1 += 2, ans2 *= dcc[i].size() * (dcc[i].size() - 1) / 2;
            else if (cnt == 1) ans1++, ans2 *= dcc[i].size() - 1;
        }
        printf("Case %d: %d %lld\n", c, ans1, ans2);
    }
    return 0;
}