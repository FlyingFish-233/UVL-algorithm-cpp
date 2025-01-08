# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n;
long long m[20] = {1}, a[20];

void exgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &m[i], &a[i]), m[0] *= m[i];
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        long long M = m[0] / m[i], x, y;
        exgcd(M, m[i], x, y), x = (x + m[i]) % m[i];
        ans = (ans + a[i] * M * x) % m[0];
    }
    printf("%lld\n", ans);
    return 0;
}