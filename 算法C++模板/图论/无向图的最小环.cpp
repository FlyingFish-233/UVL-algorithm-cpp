// POJ1734 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 110;
const int INF = 0x3f3f3f3f;

int n, m, ans = INF;
int f[NR][NR], g[NR][NR], pos[NR][NR];
vector<int> path;

void getPath(int x, int y)
{
    if (pos[x][y] == 0) return;
    getPath(x, pos[x][y]);
    path.push_back(pos[x][y]);
    getPath(pos[x][y], y);
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; i++) g[i][i] = 0;
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), g[x][y] = g[y][x] = min(g[x][y], w);
    memcpy(f, g, sizeof(g));
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++)
            for (int j = i + 1; j < k; j++)
                if (ans > (long long) f[i][j] + g[j][k] + g[k][i]) {
                    ans = f[i][j] + g[j][k] + g[k][i];
                    path.clear(), path.push_back(i), getPath(i, j);
                    path.push_back(j), path.push_back(k);
                }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (f[i][j] > f[i][k] + f[k][j])
                    f[i][j] = f[i][k] + f[k][j], pos[i][j] = k;
    }
    if (ans == INF) {
        printf("No solution.\n");
        return 0;
    }
    for (int i = 0; i < (int) path.size(); i++)
        printf("%d ", path[i]);
    puts("");
    return 0;
}