# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e7 + 10;

int n, m;
int v[NR], p[NR], phi[NR];
long long sum[NR];

int main()
{
    scanf("%d", &n);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (v[i] == 0) v[i] = p[++m] = i, phi[i] = i - 1;
        for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= n; j++) {
            v[i * p[j]] = p[j];
            if (i % p[j] == 0) phi[i * p[j]] = phi[i] * p[j];
            else phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + phi[i];
    long long ans = 0;
    for (int i = 1; i <= m; i++)
        ans += 2 * sum[n / p[i]] - 1;
    printf("%lld\n", ans);
    return 0;
}