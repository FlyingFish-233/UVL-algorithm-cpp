// AcWing9 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 110;

int n, m;
int c[NR], w[NR][NR], v[NR][NR];
int f[MR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        for (int j = 1; j <= c[i]; j++)
            scanf("%d%d", &w[i][j], &v[i][j]);
    }
    memset(f, -0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 1; k <= c[i]; k++) if (j >= w[i][k])
                f[j] = max(f[j], f[j - w[i][k]] + v[i][k]);
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}