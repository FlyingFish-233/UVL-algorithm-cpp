# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;

using namespace std;

LL gcd(LL a, LL b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

void exgcd(LL a, LL b, LL &x, LL &y)
{
    if (b == 0) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}

LL solve(LL a, LL b, LL p)
{
    LL x, y, d = gcd(a, p);
    if (b % d != 0) return -1;
    exgcd(a, p, x, y), x *= b / d;
    LL t = abs(p / d);
    x = (x % t + t) % t;
    return x;
}

int main()
{
    LL x, y, m, n, l;
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    LL ans = solve(m - n, y - x, l);
    if (ans == -1) printf("Impossible\n");
    else printf("%lld\n", ans);
    return 0;
}