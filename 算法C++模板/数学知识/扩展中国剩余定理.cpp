// P4777 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;
typedef unsigned long long uLL;

using namespace std;

int n;

LL qmul(LL a, LL b, LL p)
{
	a %= p, b %= p;
	uLL c = (long double) a * b / p;
	uLL x = a * b, y = c * p;
	long long ans = (LL) (x % p) - (LL) (y % p);
	if (ans < 0) ans += p;
	return ans;
}

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
	LL x = 0, m = 1;
	for (int i = 1; i <= n; i++) {
		LL mi, a, t, y;
		scanf("%lld%lld", &mi, &a); // x' = x + m * t -> m * t = a - x (mod mi)
		a = (a - x % mi + mi) % mi;
		if (a % gcd(m, mi) != 0) return printf("-1\n"), 0;
		exgcd(m, mi, t, y), t = (t + mi) % mi;
		t = qmul(t, a / gcd(m, mi), mi);
		LL m_new = m / gcd(m, mi) * mi;
		x = (x + qmul(m, t, m_new)) % m_new;
		m = m_new, x = (x + m) % m;
	}
	printf("%lld\n", x);
	return 0;
}
