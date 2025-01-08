# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 100, MR = 3e3 + 10;

int n, m, e;
char str[NR][NR];
int tot, l[NR][NR], up[NR][NR];
vector<int> g[MR];

bool vis[MR];
int opp[MR];

bool find(int x)
{
    if (vis[x]) return false;
    vis[x] = true;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (opp[y] == 0 || find(opp[y]))
            { opp[y] = x; return true; }
    }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int k = 1; T--; k++) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%s", str[i] + 1);
        for (int i = 0; i <= n; i++) str[i][0] = '#';
        for (int i = 0; i <= m; i++) str[0][i] = '#';
        tot = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                if (str[i][j] == '#') up[i][j] = l[i][j] = ++tot;
                else up[i][j] = up[i - 1][j], l[i][j] = l[i][j - 1];
        for (int i = 1; i <= tot; i++) g[i].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (str[i][j] == 'o') g[up[i][j]].push_back(l[i][j]);
        memset(opp, 0, sizeof(opp));
        int ans = 0;
        for (int i = 1; i <= tot; i++) {
            memset(vis, false, sizeof(vis));
            ans += find(i);
        }
        printf("Case :%d\n", k);
        printf("%d\n", ans);
    }
    return 0;
}