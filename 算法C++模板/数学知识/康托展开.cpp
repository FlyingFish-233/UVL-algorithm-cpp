// P5367 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;
const int mod = 998244353;

int n;
int a[NR];
int fac[NR], s[NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int x, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
		s[i] += delta;
}

int getsum(int x)
{
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += s[i];
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	int ans = 1;
	for (int i = 1; i <= n; i++)
		(ans += 1ll * (a[i] - 1 - getsum(a[i])) * fac[n - i] % mod) %= mod, modify(a[i], 1);
	printf("%d\n", ans);
    return 0;
}