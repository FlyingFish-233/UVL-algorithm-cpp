# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
bool f[NR][NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) f[i][i] = true;
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), f[x][y] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] |= f[i][k] && f[k][j];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d ", f[i][j]);
        puts("");
    }
    return 0;
}