# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;

using namespace std;

const LL INF = 1e18;

int n;

LL gcd(LL x, LL y)
{
	if (y == 0) return x;
	return gcd(y, x % y);
}

LL phi(LL x)
{
	LL ans = x;
	for (LL i = 2; i * i <= x; i++)
		if (x % i == 0) {
			ans = ans / i * (i - 1);
			while (x % i == 0) x /= i;
		}
	if (x > 1) ans = ans / x * (x - 1);
	return ans;
}

LL fastMul(LL a, LL b, LL mod)
{
	a %= mod, b %= mod;
	unsigned long long c = (long double) a * b / mod;
	unsigned long long x = a * b, y = c * mod;
	return ((long long) (x % mod) - (long long) (y % mod) + mod) % mod;
}

LL fastPow(LL a, LL b, LL mod)
{
	LL ans = 1;
	for (LL i = b; i > 0; i >>= 1, a = fastMul(a, a, mod) % mod)
		if (i & 1) ans = fastMul(ans, a, mod) % mod;
	return ans;
}

LL solve(LL x)
{
	LL mod = 9 * x / gcd(8, x), t = phi(mod), ans = INF;
	for (LL i = 1; i * i <= t; i++) if (t % i == 0) {
		if (fastPow(10, i, mod) == 1) ans = min(ans, i);
		if (i * i != t && fastPow(10, t / i, mod) == 1) ans = min(ans, t / i);
	}
	return ans;
}

int main()
{
	for (int i = 1; scanf("%lld", &n) && n; i++) {
		printf("Case %d: ", i);
		LL ans = solve(n);
		if (ans == INF) printf("0\n");
		else printf("%lld\n", ans);
	}
	return 0;
}