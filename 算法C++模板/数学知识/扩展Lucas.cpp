// P4720 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef long long LL;

LL qpow(LL a, LL b, LL p)
{
    LL ans = 1;
    for (LL i = b; i; i >>= 1, a = 1ll * a * a % p)
        if (i & 1) ans = ans * a % p;
    return ans % p;
}

void exgcd(LL a, LL b, LL &x, LL &y)
{
    if (b == 0) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}

LL inv(LL a, LL p)
{
    LL x, y;
    exgcd(a, p, x, y);
    return (x + p) % p;
}

// g(n, p) = n!中p的个数
LL g(LL n, LL p)
{
    if (n < p) return 0;
    return g(n / p, p) + n / p;
}

// f(n, p, pk) = n! / p^g(n,p) mod p^k
LL f(LL n, LL p, LL pk)
{
    if (n == 0) return 1;
    LL sum = 1;
    for (LL i = 1; i <= pk; i++)
        if (i % p != 0) (sum *= i) %= pk;
    sum = qpow(sum, n / pk, pk);
    for (LL i = 1; i <= n % pk; i++)
        if (i % p != 0) (sum *= i) %= pk;
    return f(n / p, p, pk) * sum % pk;
}

LL C(LL n, LL m, LL p, LL pk)
{
    return f(n, p, pk) * inv(f(m, p, pk), pk) % pk * inv(f(n - m, p, pk), pk) % pk
            * qpow(p, g(n, p) - g(m, p) - g(n - m, p), pk) % pk;
}

LL a[1000], b[1000];

LL exLucas(LL n, LL m, LL p)
{
    LL tmp = p, cnt = 0;
    for (int i = 2; i * i <= tmp; i++) if (tmp % i == 0) {
        LL save = 1;
        while (tmp % i == 0) tmp /= i, save = save * i;
        a[++cnt] = C(n, m, i, save), b[cnt] = save;
    }
    if (tmp > 1) a[++cnt] = C(n, m, tmp, tmp), b[cnt] = tmp;
    LL ans = 0;
    for (int i = 1; i <= cnt; i++)
        (ans += p / b[i] * inv(p / b[i] % b[i], b[i]) % p * a[i] % p) %= p;
    return ans;
}

int main()
{
    LL n, m, p;
    scanf("%lld%lld%lld", &n, &m, &p);
    printf("%lld\n", exLucas(n, m, p));
    return 0;
}