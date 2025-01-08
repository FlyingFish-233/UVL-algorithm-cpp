# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int mod = 11380;

int L1, L2, L3, D;
int f[31][11][11][11];

int main()
{
    scanf("%d%d%d%d", &L1, &L2, &L3, &D);
    for (int d = 0; d <= D; d++)
        f[d][0][0][0] = 1;
    for (int d = 1; d <= D; d++)
    for (int i = 0; i <= L1; i++)
    for (int j = 0; j <= L2; j++)
    for (int k = 0; k <= L3; k++) {
        if (i > 0) {
            for (int p = 1; p <= i; p++)
            for (int q = 0; q <= j; q++)
            for (int r = 0; r <= k; r++)
                (f[d][i][j][k] += f[d - 1][p - 1][q][r] * f[d][i - p][j - q][k - r]) %= mod;
        }
        if (j > 0) {
            for (int q = 1; q <= j; q++)
            for (int r = 0; r <= k; r++)
                (f[d][i][j][k] += f[d - 1][0][q - 1][r] * f[d][i][j - q][k - r]) %= mod;
        }
        if (k > 0) {
            for (int r = 1; r <= k; r++)
                (f[d][i][j][k] += f[d - 1][0][0][r - 1] * f[d][i][j][k - r]) %= mod;
        }
    }
    printf("%d\n", (f[D][L1][L2][L3] - (D ? f[D - 1][L1][L2][L3] : 0) + mod) % mod);
    return 0;
}