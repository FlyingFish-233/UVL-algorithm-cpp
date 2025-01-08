// P7519 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n, m, a_max;
int a[15];
long long f[8200][15][510]; // f[sta][i][j]表示已选了sta, 目前最后一项为i, 总和为j的方案数

int p[8200];

int lowbit(int x)
{
    return x & (-x);
}

// b[i1] <= b[i2] <= ... <= b[in]
// a[a_max] <= a[i1] + b[i1] <= a[i2] + b[i2] <= ... <= a[in] + b[in]
// b[i1] >= a[a_max] - a[i1] + (a_max < i1), b[i2] - b[i1] >= max(a[i1] - a[i2] + (i1 < i2), 0), ...
// m >= Sum(b) >= Sum(max(a[i(k)] - a[i(k-1)] + (i(k) < i(k-1)), 0) * (n - k + 1))
// f[sta][i][j] -> f[sta | (1 << i0)][i0][j + max(a[i] - a[i0] + (i < i0), 0) * (n - cnt[sta])]
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        p[1 << i] = i;
    int lim = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[a_max] < a[i]) a_max = i;
    }
    for (int i = 0; i < n; i++) {
        int j0 = n * (a[a_max] - a[i] + (a_max < i));
        if (j0 <= m) f[1 << i][i][j0] = 1;
    }
    for (int sta = 0; sta <= lim; sta++) {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += sta >> i & 1;
        for (int sta1 = sta; sta1; sta1 -= lowbit(sta1))
            for (int j = 0; j <= m; j++)
                for (int sta2 = lim - sta; sta2; sta2 -= lowbit(sta2)) {
                    int i = p[lowbit(sta1)], i0 = p[lowbit(sta2)];
                    int j0 = j + max(a[i] - a[i0] + (i < i0), 0) * (n - cnt);
                    if (j0 <= m) f[sta | (1 << i0)][i0][j0] += f[sta][i][j];
                }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            ans += f[lim][i][j];
    printf("%lld\n", ans);
    return 0;
}

