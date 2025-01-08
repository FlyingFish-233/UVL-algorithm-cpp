// P5180 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 2e5 + 10;

int n, m;
vector<int> g[3][NR];

int now, dfn[NR], ord[NR], fa[NR];

void tarjan(int x)
{
    ord[dfn[x] = ++now] = x;
    for (int i = 0; i < (int) g[0][x].size(); i++) {
        int y = g[0][x][i];
        if (dfn[y] == 0) fa[y] = x, tarjan(y);
    }
}

int sdom[NR], idom[NR];
int uni[NR], pos[NR];

int find(int x)
{
    if (uni[x] == x) return x;
    int save = find(uni[x]);
    if (dfn[sdom[pos[uni[x]]]] < dfn[sdom[pos[x]]]) pos[x] = pos[uni[x]];
    return uni[x] = save;
}

void lengauer_tarjan(int s)
{
    tarjan(s);
    for (int i = 1; i <= n; i++)
        sdom[i] = uni[i] = pos[i] = i;
    for (int k = n; k >= 2; k--) {
        int x = ord[k];
        for (int i = 0; i < (int) g[1][x].size(); i++) {
            int y = g[1][x][i];
            if (dfn[y] == 0) continue;
            find(y);
            if (dfn[sdom[pos[y]]] < dfn[sdom[x]]) sdom[x] = sdom[pos[y]];
        }
        uni[x] = fa[x], g[2][sdom[x]].push_back(x), x = fa[x];
        for (int i = 0; i < (int) g[2][x].size(); i++) {
            int y = g[2][x][i];
            find(y);
            idom[y] = (x == sdom[pos[y]]) ? x : pos[y];
        }
        g[2][x].clear();
    }
    for (int k = 2; k <= n; k++) {
        int x = ord[k];
        if (idom[x] != sdom[x]) idom[x] = idom[idom[x]];
    }
}

int ans[NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[0][x].push_back(y), g[1][y].push_back(x);
    lengauer_tarjan(1);
    for (int i = n; i >= 2; i--)
        ans[idom[ord[i]]] += (++ans[ord[i]]);
    ans[1]++;
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}