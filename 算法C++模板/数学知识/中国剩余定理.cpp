// P1495 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 20;

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

int n; long long m = 1;
int a[NR], b[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i], &b[i]), m *= a[i];
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		(ans += m / a[i] * inv(m / a[i] % a[i], a[i]) % m * b[i] % m) %= m;
	printf("%lld\n", ans);
 	return 0;
}

