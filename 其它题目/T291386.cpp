# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n, c;
int cnt[NR];
long long sum[NR], f[NR];

long long getsum(int l, int r)
{
    l = (l + c) % c, r = (r + c) % c;
    if (l == 0) return sum[r];
    if (l <= r) return sum[r] - sum[l - 1];
    return sum[c - 1] - sum[l - 1] + sum[r];
}

int main()
{
    scanf("%d%d", &n, &c);
    if (c <= 2 || c == 4) return printf("0\n"), 0;
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), cnt[x]++;
    sum[0] = cnt[0];
    for (int i = 1; i <= c - 1; i++)
        sum[i] = sum[i - 1] + cnt[i];
    if (c % 2 == 0) {
        int k = c / 2;
        for (int i = 1; i <= k - 2; i++)
            f[0] += cnt[i + 1] * getsum(1 + k, i + k);
        for (int i = 0; i <= c - 2; i++)
            f[i + 1] = f[i] - cnt[(i + 1 + k)%c] * getsum(i + 2, i + k - 1) + cnt[(i + k)%c] * getsum(i + 2 + k, i - 1);
    }
    else {
        int k = (c - 1) / 2;
        for (int i = 1; i <= k; i++)
            f[0] += cnt[i] * getsum(1 + k, i + k);
        for (int i = 0; i <= c - 2; i++)
            f[i + 1] = f[i] - cnt[(i + 1 + k)%c] * getsum(i + 1, i + k) + cnt[(i + 1 + k)%c] * getsum(i + 2 + k, i);
    }
    long long ans = 0;
    for (int i = 0; i <= c - 1; i++)
        ans += cnt[i] * f[i];
    printf("%lld\n", ans / 3);
    return 0;
}


