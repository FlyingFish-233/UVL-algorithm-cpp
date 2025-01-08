// P4718 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

# define lll __int128

long long qpow(long long a, long long b, long long mod)
{
    long long sum = 1;
    for (long long i = b; i; i >>= 1, a = (lll)a * a % mod)
        if (i & 1) sum = (lll)sum * a % mod;
    return sum;
}

bool millerRabin(long long x)
{
    if (x <= 2 || x % 2 == 0) return x == 2;
    long long a = x - 1, b = 0;
    while (a % 2 == 0) a /= 2, b++;
    for (int i = 1; i <= 10; i++) {
        long long y = qpow(rand() % (x - 2) + 2, a, x), j;
        if (y == 1) continue;
        for (j = 0; j < b && y != x - 1; j++)
            y = (lll)y * y % x;
        if (j == b) return false;
    }
    return true;
}

long long gcd(long long a, long long b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

long long pollardRho(long long x)
{
    long long c = rand() % (x - 1) + 1;
    long long s = 0, t = 0, now = 1;
    for (int goal = 1; ; goal <<= 1, s = t) {
        for (int step = 1; step <= goal; step++) {
            t = ((lll)t * t + c) % x;
            now = (lll)now * abs(t - s) % x;
            if (step % 127 == 0) {
                long long d = gcd(now, x);
                if (d > 1) return d;
            }
        }
        long long d = gcd(now, x);
        if (d > 1) return d;
    }
    return x;
}

long long max_factor = 0;

void fac(long long x)
{
    if (x <= max_factor || x < 2) return;
    if (millerRabin(x)) { max_factor = x; return; }
    long long y = pollardRho(x);
    while (x % y == 0) x /= y;
    fac(x), fac(y);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n;
        scanf("%lld", &n);
        max_factor = 0, fac(n);
        if (max_factor == n) printf("Prime\n");
        else printf("%lld\n", max_factor);
    }
    return 0;
}