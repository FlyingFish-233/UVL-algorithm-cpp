# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int f[NR][NR];

int main()
{
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), f[x][y] = min(f[x][y], w);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d ", (f[i][j] == INF) ? -1 : f[i][j]);
        puts("");
    }
    return 0;
}