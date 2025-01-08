// P3807 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 1e5 + 10;

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

int factor[NR];

int C(int n, int m, int p)
{
	if (m > n) return 0;
	return 1ll * factor[n] * inv(factor[m], p) % p * inv(factor[n - m], p) % p;
}

int Lucas(int n, int m, int p)
{
	if (m == 0) return 1;
	return 1ll * C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, p;
		scanf("%d%d%d", &n, &m, &p);
		factor[0] = 1;
		for (int i = 1; i <= p; i++)
			factor[i] = 1ll * factor[i - 1] * i % p;
		printf("%d\n", Lucas(n + m, n, p));
	}
 	return 0;
}

