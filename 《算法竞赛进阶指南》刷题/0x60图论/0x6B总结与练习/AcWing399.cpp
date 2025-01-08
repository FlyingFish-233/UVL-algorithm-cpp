# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 50, MR = 2000;

int n, m;
vector< pair<int, int> > g[NR];

bool vis[MR];
int len, fte[NR], ans[MR];

void euler(int x)
{
    for (int i = fte[x]; i < (int) g[x].size(); i = fte[x]) {
        int id = g[x][i].first, y = g[x][i].second; fte[x] = i + 1;
        if (!vis[id]) vis[id] = true, euler(y), ans[++len] = id;
    }
}

int main()
{
    while (true) {
        for (int i = 1; i <= 44; i++) g[i].clear();
        int x, y, z, s = 0; n = 0;
        while (true) {
            scanf("%d%d", &x, &y);
            if (s == 0 && x == 0 && y == 0) return 0;
            if (x == 0 && y == 0) break;
            scanf("%d", &z);
            if (s == 0) s = min(x, y);
            n = max(n, max(x, y));
            g[x].push_back({z, y}), g[y].push_back({z, x});
        }
        bool flag = true;
        for (int i = 1; i <= n; i++)
            if (g[i].size() % 2 == 1) flag = false;
        if (!flag) { printf("Round trip does not exist.\n"); continue; }
        memset(vis, false, sizeof(vis));
        memset(fte, 0, sizeof(fte)), len = 0;
        for (int i = 1; i <= n; i++)
            sort(g[i].begin(), g[i].end());
        euler(s);
        reverse(ans + 1, ans + len + 1);
        for (int i = 1; i <= len; i++)
            printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}