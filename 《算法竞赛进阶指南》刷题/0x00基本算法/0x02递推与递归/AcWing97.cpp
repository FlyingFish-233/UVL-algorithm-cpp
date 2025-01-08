# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10, mod = 9901;

int n, m;
int num, p[NR], a[NR];

void solve(int x)
{
	for (int i = 2; i <= x; i++)
		if (x % i == 0) {
			p[++num] = i;
			for ( ; x % i == 0; x /= i)
				a[num]++;
		}
}

int power(int a, int b)
{
	int sum = 1;
	for (int i = b; i; i >>= 1, a = 1ll * a * a % mod)
		if (i & 1) sum = 1ll * sum * a % mod;
	return sum % mod;
}

int getsum(int a, long long b)
{
	if (a == 0) return 0;
	if (b == 0) return 1;
	int ans = getsum(a, b / 2);
	ans = 1ll * ans * (1 + power(a, b / 2 + 1)) % mod;
	if (!(b & 1)) ans = (ans - power(a, b + 1) + mod) % mod;
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	if (n == 0) {
		printf("0\n");
		return 0;
	}
	solve(n);
	int ans = 1;
	for (int i = 1; i <= num; i++)
		ans = 1ll * ans * getsum(p[i], 1ll * a[i] * m) % mod;
	printf("%d\n", ans);
	return 0;
}