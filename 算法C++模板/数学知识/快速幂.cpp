// P1226 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int qpow(int a, int b, int p)
{
	int ans = 1;
	for (int i = b; i; i >>= 1, a = 1ll * a * a % p)
		if (i & 1) ans = 1ll * ans * a % p;
	return ans % p;
}

int main()
{
	int a, b, p;
	scanf("%d%d%d", &a, &b, &p);
	printf("%d^%d mod %d=%d\n", a, b, p, qpow(a, b, p));
	return 0;
}