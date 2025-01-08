// P4782 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 2e6 + 10;

int n, m;
vector<int> g[NR];

void addEdge(int x, int y)
{
    g[x].push_back(y);
}

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
    while (s.top() != x) {
        int y = s.top();
        c[y] = tot;
        ins[y] = false, s.pop();
    }
    ins[x] = false, s.pop();
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, z, w; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &z, &w);
        g[x + (!y) * n].push_back(z + w * n);
        g[z + (!w) * n].push_back(x + y * n);
    }
    for (int i = 1; i <= 2 * n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (c[i] == c[i + n]) return printf("IMPOSSIBLE\n"), 0;
    printf("POSSIBLE\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", (c[i] < c[i + n]) ? 0 : 1);
    puts("");
    return 0;
}