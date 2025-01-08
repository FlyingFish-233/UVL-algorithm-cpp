// P2679 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1010, MR = 210;
const int mod = 1e9 + 7;

int n, m, k;
char s1[NR], s2[NR];
int f[2][NR][MR], sum[NR][MR];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", s1 + 1, s2 + 1);
    for (int i = 0; i <= n; i++)
        f[0][i][0] = 1;
    for (int t = 1; t <= k; t++) {
        memset(f[1], 0, sizeof(f[1]));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (s1[i] == s2[j]) sum[i][j] = (sum[i - 1][j - 1] + f[0][i - 1][j - 1]) % mod;
                else sum[i][j] = 0;
                f[1][i][j] = (f[1][i - 1][j] + sum[i][j]) % mod;
            }
        memcpy(f[0], f[1], sizeof(f[1]));
    }
    printf("%d\n", f[0][n][m]);
    return 0;
}

