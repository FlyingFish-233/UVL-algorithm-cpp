// P4195 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>
# include <map>

using namespace std;

int gcd(int x, int y)
{
	if (y == 0) return x;
	return gcd(y, x % y);
}

void exgcd(int a, int b, int &x, int &y)
{
	if (b == 0) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}

int inv(int a, int p)
{
	int x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

int bsgs(int a, int b, int p)
{
	a %= p, b %= p;
	if (b == 1 || p == 1) return 0;
	if (a == 0) return (b == 0) ? 1 : -1;
	map<int, int> hash;
	int t = sqrt(p) + 1, A = 1;
	for (int j = 0; j <= t - 1; j++, A = 1ll * A * a % p)
		hash[1ll * b * A % p] = j;
	a = A, A = 1;
	for (int i = 0; i <= t; i++, A = 1ll * A * a % p) {
		int j = (hash.count(A) == 0) ? -1 : hash[A];
		if (j >= 0 && i * t - j >= 0) return i * t - j;
	}
	return -1;
}

// a^k/d * a^x = b/d (mod p/d)
int exbsgs(int a, int b, int p)
{	
	a %= p, b %= p;
	if (b == 1 || p == 1) return 0;
	if (a == 0) return (b == 0) ? 1 : -1;
	int d, k = 0, s = 1;
	while (d = gcd(a, p), d > 1) {
		if (b % d != 0) return -1;
		b /= d, p /= d, s = 1ll * s * (a / d) % p, k++;
		if (s == b) return k;
	}
	b = 1ll * b * inv(s, p) % p;
	int ans = bsgs(a, b, p);
	return (ans == -1) ? -1 : ans + k;
}

int main()
{
	int a, b, p;
	while (scanf("%d%d%d", &a, &p, &b) && !(a == 0 && b == 0 && p == 0)) {
		int ans = exbsgs(a, b, p);
		if (ans == -1) printf("No Solution\n");
		else printf("%d\n", ans);
	}
 	return 0;
}
