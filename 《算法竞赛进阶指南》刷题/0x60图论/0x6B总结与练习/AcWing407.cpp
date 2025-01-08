# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
int g[NR][30], v[30];

bool vis[NR];
int opp[30][NR], cnt[NR];

bool find(int x, int l, int r)
{
    for (int i = l; i <= r; i++) {
        int y = g[x][i];
        if (vis[y]) continue;
        vis[y] = true;
        if (cnt[y] < v[y]) { opp[y][++cnt[y]] = x; return true; }
        else 
            for (int j = 1; j <= v[y]; j++)
                if (find(opp[y][j], l, r)) { opp[y][j] = x; return true; }
    }
    return false;
}

bool hungary(int l, int r)
{
    memset(opp, 0, sizeof(opp));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (!find(i, l, r)) return false;
    }
    return true;
}

bool check(int mid)
{
    for (int l = 1; l <= m - mid + 1; l++)
        if (hungary(l, l + mid - 1)) return true;
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &g[i][j]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &v[i]);
    int l = 1, r = m, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    printf("%d\n", ans);    
    return 0;
}