// AcWing8 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 110;

int n, m1, m2;
int w1[NR], w2[NR], v[NR];
int f[MR][MR];

int main()
{
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &w1[i], &w2[i], &v[i]);
    memset(f, -0x3f, sizeof(f)), f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m1; j >= w1[i]; j--)
            for (int k = m2; k >= w2[i]; k--)
                f[j][k] = max(f[j][k], f[j - w1[i]][k - w2[i]] + v[i]);
    int ans = 0;
    for (int i = 0; i <= m1; i++)
        for (int j = 0; j <= m2; j++)
            ans = max(ans, f[i][j]);
    printf("%d\n", ans);
    return 0;
}