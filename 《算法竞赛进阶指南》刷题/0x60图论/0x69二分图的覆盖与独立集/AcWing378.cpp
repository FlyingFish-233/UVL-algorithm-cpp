# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 1e4 + 10;
const int nxt[10][2] = {{0, 0}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

struct Edge
{
    int to, next;
};

int n, m, t;
bool flag[NR][NR];

int gsz, fte[MR];
Edge g[MR << 3];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

bool vis[MR];
int opp[MR];

bool find(int x)
{
    if (vis[x]) return false;
    vis[x] = true;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
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
        for (int y = 1; y <= m; y++) if ((x + y) % 2 == 0 && !flag[x][y])
            for (int i = 1; i <= 8; i++) {
                int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
                if (x0 >= 1 && x0 <= n && y0 >= 1 && y0 <= m && !flag[x0][y0])
                    addEdge((x - 1) * m + y, (x0 - 1) * m + y0);
            }
    int ans = 0;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++) if ((x + y) % 2 == 0 && !flag[x][y]) {
            memset(vis, false, sizeof(vis));
            ans += find((x - 1) * m + y);
        }
    printf("%d\n", n * m - t - ans);
    return 0;
}