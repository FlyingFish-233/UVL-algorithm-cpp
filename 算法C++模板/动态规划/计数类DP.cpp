// AcWing306 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define x first
# define y second

using namespace std;

const int NR = 2e3 + 10, MR = 2e5 + 10;
const int mod = 1e9 + 7;

int h, w, n;
pair<int, int> a[NR];
int jc[MR], jc_inv[MR];
int f[NR];

int fastPow(int a, int b)
{
    int sum = 1;
    for (int i = b; i; i >>= 1, a = 1ll * a * a % mod)
        if (i & 1) sum = 1ll * sum * a % mod;
    return sum;
}

int C(int a, int b)
{
    return 1ll * jc[a] * jc_inv[b] % mod * jc_inv[a - b] % mod;
}

// f[i]表示从左上角走到第i个黑格, 并且途中不经过其他黑格的路线数
// f[i] = C(xi-1+yi-1, xi-1) - Sum(f[j] * C(xi-xj+yi-yj, xi-xj)) 其中xi >= xj, yi >= yj, 1 <= j < i
int main()
{
    jc[0] = jc_inv[0] = 1;
    for (int i = 1; i <= 2e5; i++)
        jc[i] = 1ll * jc[i - 1] * i % mod, jc_inv[i] = fastPow(jc[i], mod - 2);
    scanf("%d%d%d", &h, &w, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1), a[n + 1] = {h, w};
    for (int i = 1; i <= n + 1; i++) {
        f[i] = C(a[i].x + a[i].y - 2, a[i].x - 1);
        for (int j = 1; j < i; j++) if (a[j].x <= a[i].x && a[j].y <= a[i].y)
            f[i] = (f[i] - 1ll * f[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x) % mod + mod) % mod;
    }
    printf("%d\n", f[n + 1]);
    return 0;
}