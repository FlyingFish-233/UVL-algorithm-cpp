# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e7 + 10;
const int mod = 9901;

int a, b;
int n, p[NR], c[NR];

void divide(int x)
{
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) {
			p[++n] = i;
			while (x % i == 0) c[n]++, x /= i;
		}
	if (x > 1) p[++n] = x, c[n] = 1;
}

int power(int a, long long b)
{
	int ans = 1;
	for (long long i = b; i; i >>= 1, a = 1ll * a * a % mod)
		if (i & 1) ans = 1ll * ans * a % mod;
	return ans;
}

int main()
{
	scanf("%d%d", &a, &b);
	if (a == 0) return printf("0\n"), 0;
	divide(a);
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		long long t = 1ll * b * c[i] + 1;
		if (p[i] % mod == 1) (ans = 1ll * ans * t % mod) %= mod;
		else ans = 1ll * ans * (power(p[i], t) - 1 + mod) % mod * power(p[i] - 1, mod - 2) % mod;
	}
	printf("%d\n", ans);
	return 0;
}