// P1447 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

long long f[NR];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = n; i >= 1; i--) {
        f[i] = 1ll * (n/i) * (m/i);
        for (int j = 2; j <= max(n, m)/i; j++)
            f[i] -= f[i * j];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += i * f[i];
    printf("%lld\n", 2 * ans - 1ll * n * m);
    return 0;
}