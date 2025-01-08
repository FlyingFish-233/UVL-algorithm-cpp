# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;

using namespace std;

int n;

LL gcd(LL x, LL y)
{
	if (y == 0) return x;
	return gcd(y, x % y);
}

void exgcd(LL a, LL b, LL &x, LL &y)
{
	if (b == 0) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}

int main()
{
	scanf("%d", &n);
	LL ans = 0, lcm = 1;
	for (int i = 1; i <= n; i++) {
		LL mod, a, x, y;
		scanf("%lld%lld", &mod, &a);
		a = (a - ans % mod + mod) % mod;
		if (a % gcd(lcm, mod) != 0) return printf("-1\n"), 0;
		exgcd(lcm, mod, x, y), x = (x + mod) % mod;
		x = x * a / gcd(lcm, mod) % mod;
		ans = ans + lcm * x;
		lcm = lcm / gcd(lcm, mod) * mod;
		ans = (ans % lcm + lcm) % lcm;
	}
	printf("%lld\n", ans);
	return 0;
}