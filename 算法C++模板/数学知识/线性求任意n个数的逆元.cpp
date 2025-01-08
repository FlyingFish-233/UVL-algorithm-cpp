// P5431 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e6 + 10;

int n, p, k;
int a[NR], s[NR];
int inv[NR], inv_s[NR];

int read()
{
	char c = getchar();
	int num = 0; bool flag = false;
	for ( ; !(c >= '0' && c <= '9'); c = getchar())
		if (c == '-') flag = true;
	for ( ; c >= '0' && c <= '9'; c = getchar())
		num = num * 10 + c - 48;
	if (flag) num = -num;
	return num;
}

int fastPow(int a, int b, int mod)
{
	int ans = 1, base = a;
	for (int i = b; i; i >>= 1) {
		if (i & 1) ans = 1ll * ans * base % mod;
		base = 1ll * base * base % mod;
	}
	return ans;
}

int main()
{
	scanf("%d%d%d", &n, &p, &k);
	s[0] = 1;
	for (int i = 1; i <= n; i++)
		a[i] = read(), s[i] = 1ll * s[i - 1] * a[i] % p;
	inv_s[n] = fastPow(s[n], p - 2, p);
	for (int i = n; i >= 1; i--)
		inv_s[i - 1] = 1ll * a[i] * inv_s[i] % p;
	for (int i = 1; i <= n; i++)
		inv[i] = 1ll * s[i - 1] * inv_s[i] % p;
	int sum = 0, base = k;
	for (int i = 1; i <= n; i++) {
		(sum += 1ll * base * inv[i] % p) %= p;
		base = 1ll * base * k % p;
	}
	printf("%d\n", sum);
    return 0;
}