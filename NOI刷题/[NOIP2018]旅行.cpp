// P5049 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 5e5 + 10;

int n, m;
vector<int> g[NR];
bool vis[NR], loop[NR];
int fa[NR], head, tail;

void get_loop(int x, int dad)
{
    vis[x] = true, fa[x] = dad;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (y == dad) continue;
        if (vis[y]) head = x, tail = y;
        else get_loop(y, x);
    }
}

int save = -1;

void dfs(int x)
{
    vis[x] = true, printf("%d ", x);
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (vis[y]) continue;
        if (save > 0 && loop[y]) {
            int j = i + 1;
            while (j < (int) g[x].size() && vis[g[x][j]]) j++;
            if (j < (int) g[x].size()) save = g[x][j];
            if (y >= save) { save = 0; break; }
        }
        if (save == -1 && x == head && loop[y]) save = g[x][i + 1];
        dfs(y);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
    for (int i = 1; i <= n; i++)
        sort(g[i].begin(), g[i].end());
    if (m == n - 1) { dfs(1); return 0; }
    get_loop(1, 0);
    loop[head] = true;
    for (int i = tail; i != head; i = fa[i])
        loop[i] = true;
    memset(vis, false, sizeof(vis));
    dfs(1);
    return 0;
}

