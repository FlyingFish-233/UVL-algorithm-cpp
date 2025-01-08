// P6657 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e6 + 10, MR = 110;
const int mod = 998244353;

int fac[NR], inv[NR], inv_fac[NR];

int C(int n, int m)
{
    return 1ll * fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int n, m;
int a[MR], b[MR];
int mat[MR][MR];

int det()
{
    int ans = 1; bool flag = false;
    for (int i = 1; i <= m; i++) {
        int row = i;
        for (int j = i + 1; j <= m; j++)
            if (mat[j][i] > mat[row][i]) row = j;
        if (mat[row][i] == 0) return 0;
        if (i != row) swap(mat[row], mat[i]), flag ^= 1;
        for (int j = i + 1; j <= m; j++) {
            if (mat[j][i] > mat[i][i]) swap(mat[i], mat[j]), flag ^= 1;
            while (mat[j][i]) {
                int rate = mat[i][i] / mat[j][i];
                for (int k = i; k <= m; k++)
                    mat[i][k] = (mat[i][k] - 1ll * mat[j][k] * rate % mod + mod) % mod;
                swap(mat[i], mat[j]), flag ^= 1;
            }
        }
        ans = 1ll * ans * mat[i][i] % mod;
    }
    if (flag) ans = (mod - ans) % mod;
    return ans;
}

int main()
{
    fac[0] = inv_fac[0] = 1;
    fac[1] = inv_fac[1] = inv[1] = 1;
    for (int i = 2; i <= 2e6; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
        inv_fac[i] = 1ll * inv_fac[i - 1] * inv[i] % mod;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &a[i], &b[i]);
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                mat[i][j] = (b[j] >= a[i]) ? C(b[j] - a[i] + n - 1, n - 1) : 0;
        printf("%d\n", det());
    }
    return 0;
}