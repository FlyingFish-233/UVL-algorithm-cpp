# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>
# include <queue>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
vector<int> g[NR];
int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> s;

int tot, c[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now;
    ins[x] = true, s.push(x);
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (dfn[y] == 0) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    c[x] = ++tot;
    while (s.top() != x)
        c[s.top()] = tot, ins[s.top()] = false, s.pop();
    ins[x] = false, s.pop();
}

int in[NR];
vector<int> G[NR];
queue<int> q;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), g[x].push_back(y);
        memset(dfn, 0, sizeof(dfn)), tot = 0;
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0) tarjan(i);
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= tot; i++) G[i].clear();
        for (int x = 1; x <= n; x++)
            for (int i = 0; i < (int) g[x].size(); i++) {
                int y = g[x][i];
                if (c[x] != c[y]) G[c[x]].push_back(c[y]), in[c[y]]++;
            }
        while (!q.empty()) q.pop();
        for (int i = 1; i <= tot; i++)
            if (in[i] == 0) q.push(i);
        bool flag = true;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (!q.empty()) { flag = false; break; }
            for (int i = 0; i < (int) G[x].size(); i++) {
                int y = G[x][i];
                if (--in[y] == 0) q.push(y);
            }
        }
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}