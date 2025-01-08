# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;

using namespace std;

const LL prime[4] = {2, 3, 4679, 35617};
const LL mod = 999911658;

LL n, q;
LL factory[40010], num[4];

LL fastPow(LL a, LL b, LL p)
{
	LL ans = 1;
	for (LL i = b; i; i >>= 1, (a *= a) %= p)
		if (i & 1) (ans *= a) %= p;
	return ans;
}

void exgcd(LL a, LL b, LL &x, LL &y)
{
	if (b == 0) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= (a / b) * x;
}

LL inv(LL a, LL p)
{
	LL x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}

LL calc(LL a, LL b, LL p)
{
	LL ans = 1;
	for (LL i = a, j = b; i && j; i /= p, j /= p) {
		LL x = i % p, y = j % p;
		if (y < x) { ans = 0; break; }
		(ans *= factory[y] * fastPow(factory[x], p - 2, p) % p * fastPow(factory[y - x], p - 2, p) % p) %= p;
	}
	return ans;
}

int main()
{
	scanf("%lld%lld", &n, &q), q %= mod + 1;
	if (q == 0) return printf("0\n"), 0;
	factory[0] = 1;
	for (int i = 1; i <= prime[3]; i++)
		factory[i] = factory[i - 1] * i % mod;
	for (LL i = 1; i * i <= n; i++) if (n % i == 0) {
		for (int j = 0; j < 4; j++)
			(num[j] += calc(i, n, prime[j])) %= prime[j];
		if (i * i == n) continue;
		for (int j = 0; j < 4; j++)
			(num[j] += calc(n / i, n, prime[j])) %= prime[j];
	}
	LL ans = 0;
	for (int i = 0; i < 4; i++) {
		LL tmp = fastPow(mod / prime[i], prime[i] - 2, prime[i]);
		(ans += num[i] * (mod / prime[i]) % mod * tmp) %= mod;
	}
	printf("%lld\n", fastPow(q, ans, mod + 1));
	return 0;
}