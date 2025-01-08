# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;

using namespace std;

const int NR = 30;
const LL mod = 1e9 + 7;

LL n, m;
LL a[NR], inv[NR];

LL fastPow(LL a, LL b)
{
	LL ans = 1;
	for (LL i = b; i; i >>= 1, (a *= a) %= mod)
		if (i & 1) (ans *= a) %= mod;
	return ans;
}

LL calc(LL a, LL b)
{
	if (a < 0 || b < 0 || a > b) return 0;
	LL ans = 1; b %= mod;
	for (int i = b; i >= b - a + 1; i--)
		(ans *= i) %= mod;
	for (int i = a; i >= 1; i--)
		(ans *= inv[i]) %= mod;
	return ans;
}

int main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	LL ans = 0;
	for (int sta = 0; sta < (1 << n); sta++) {
		LL sum = n + m, num = 0;
		for (int i = 0; i < n; i++)
			if (sta >> i & 1) sum -= a[i], num++;
		sum -= num + 1;
		(ans += mod + ((num & 1) ? -1 : 1) * calc(n - 1, sum)) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}