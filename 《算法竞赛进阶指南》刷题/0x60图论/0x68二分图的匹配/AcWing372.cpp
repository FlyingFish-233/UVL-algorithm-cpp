# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 110, MR = 1e4 + 10;
const int nxt[5][2] = {{0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int n, m;
bool flag[NR][NR];

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
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), flag[x][y] = true;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= n; y++) if ((x + y) % 2 == 0 && !flag[x][y])
            for (int k = 1; k <= 4; k++) {
                int x0 = x + nxt[k][0], y0 = y + nxt[k][1];
                if (x0 >= 1 && x0 <= n && y0 >= 1 && y0 <= n && !flag[x0][y0]) 
                    g[(x - 1) * n + y].push_back((x0 - 1) * n + y0);
            }
    int ans = 0;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= n; y++) if ((x + y) % 2 == 0 && !flag[x][y]) {
            memset(vis, false, sizeof(vis));
            ans += find((x - 1) * n + y);
        }
    printf("%d\n", ans);
    return 0;
}