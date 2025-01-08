# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 100;

int n, m;
int opp[NR];
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

int main()
{
    while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
        for (int i = 1; i <= n; i++)
            opp[i] = i + n, opp[i + n] = i;
        for (int i = 1; i <= 2 * n; i++) g[i].clear();
        g[1].push_back(1 + n);
        for (int i = 1; i <= m; i++) {
            int x, y; char c1, c2;
            scanf("%d%c %d%c", &x, &c1, &y, &c2), x++, y++;
            if (c1 == 'h') x += n;
            if (c2 == 'h') y += n;
            g[x].push_back(opp[y]);
            g[y].push_back(opp[x]);
        }
        memset(dfn, 0, sizeof(dfn));
        for (int i = 1; i <= 2 * n; i++)
            if (dfn[i] == 0) tarjan(i);
        bool flag = true;
        for (int i = 1; i <= n; i++)
            if (c[i] == c[i + n]) { flag = false; break; }
        if (!flag) { printf("bad luck\n"); continue; }
        for (int i = 2; i <= n; i++)
            printf("%d%c ", i - 1, (c[i] < c[i + n]) ? 'h' : 'w');
        puts("");
    }
    return 0;
}