# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
vector<int> g[NR];
int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> s;

int tot, c[NR], sz[NR];

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
    c[x] = ++tot, sz[tot] = 1;
    while (s.top() != x) {
        int y = s.top();
        c[y] = tot, sz[tot]++;
        ins[y] = false, s.pop();
    }
    ins[x] = false, s.pop();
}

int in[NR];
bool vis[NR];
vector<int> G[NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int x = 1; x <= n; x++) {
        for (int i = 0; i < (int) g[x].size(); i++) {
            int y = g[x][i];
            if (c[x] != c[y] && !vis[c[y]]) {
                vis[c[y]] = true;
                G[c[x]].push_back(c[y]), in[c[y]]++;
            }
        }
        for (int i = 0; i < (int) g[x].size(); i++)
            vis[c[g[x][i]]] = false;
    }
    int cnt = 0; bool flag = false;
    for (int i = 1; i <= tot; i++)
        if (in[i] == 0) {
            cnt++;
            if (sz[i] == 1 && !flag) {
                bool flag2 = true;
                for (int j = 0; j < (int) G[i].size(); j++)
                    if (in[G[i][j]] <= 1) { flag2 = false; break; }
                if (flag2) flag = true;
            }
        }
    printf("%.6f\n", 1.0 * (n - cnt + flag) / n);
    return 0;
}