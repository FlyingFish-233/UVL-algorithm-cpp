# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int mod = 1e4 + 7;

int inv[mod];

int fastPow(int a, int b)
{
	int ans = 1;
	for (int i = b; i; i >>= 1, a = 1ll * a * a % mod)
		if (i & 1) ans = 1ll * ans * a % mod;
	return ans;
}

int main()
{
	int a, b, k, n, m;
	scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
	a %= mod, b %= mod;
	inv[1] = 1;
	for (int i = 2; i < mod; i++)
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	a = fastPow(a, n), b = fastPow(b, m);
	int ans = 1ll * a * b % mod;
	for (int i = k; i >= k - n + 1; i--)
		ans = 1ll * ans * i % mod;
	for (int i = n; i >= 1; i--)
		ans = 1ll * ans * inv[i] % mod;
	printf("%d\n", ans);
	return 0;
}