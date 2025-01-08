// AcWing90 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

long long mul(long long a, long long b, long long p)
{
	long long ans = 0;
	for (long long i = b; i; i >>= 1, a = (a + a) % p)
		if (i & 1) ans = (ans + a) % p;
	return ans % p;
}

int main()
{
	long long a, b, p;
	scanf("%lld%lld%lld", &a, &b, &p);
	printf("%lld\n", mul(a, b, p));
	return 0;
}