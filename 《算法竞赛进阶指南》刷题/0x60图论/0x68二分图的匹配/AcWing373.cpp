# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 210;

int n, m, t;
bool flag[NR][NR];

vector<int> g[NR];
bool vis[NR];
int opp[NR];

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
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1, x, y; i <= t; i++)
        scanf("%d%d", &x, &y), flag[x][y] = true;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++) 
            if (!flag[x][y]) g[x].push_back(y);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));
        ans += find(i);
    }
    printf("%d\n", ans);
    return 0;
}