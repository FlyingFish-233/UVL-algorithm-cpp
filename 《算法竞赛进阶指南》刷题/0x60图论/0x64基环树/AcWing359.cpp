# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e6 + 10;

int n;
int fa[NR];
vector<int> g[NR];

int rt, f[NR][2];
bool vis[NR];

void dfs(int x, bool type)
{
    f[x][0] = 0, vis[x] = true;
    int f_min = 2e9;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (y == rt) continue;
        dfs(y, type);
        f_min = min(f_min, max(f[y][0], f[y][1]) - f[y][0]);
        f[x][0] += max(f[y][0], f[y][1]);
    }
    if (type && x == fa[rt]) f[x][1] = f[x][0] + 1;
    else f[x][1] = f[x][0] - f_min + 1;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &fa[i]), g[fa[i]].push_back(i);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            for (rt = i; !vis[rt]; rt = fa[rt])
                vis[rt] = true;
            dfs(rt, 0);
            int save = max(f[rt][0], f[rt][1]);
            dfs(rt, 1);
            ans += max(save, f[rt][0]);
        }
    printf("%d\n", ans);
    return 0;
}