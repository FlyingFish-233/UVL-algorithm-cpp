# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;
const int INF = 0x3f3f3f3f;

int n, m;
int f[NR][NR];

int main()
{
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), f[x][y] = f[y][x] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (f[i][j] < INF) ans = max(ans, f[i][j]);
    printf("%d\n", ans);
    return 0;
}