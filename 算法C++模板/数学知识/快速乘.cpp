// AcWing90 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long ull;

long long mul(long long a, long long b, long long p)
{
	a %= p, b %= p;
	ull c = (long double) a * b / p;
	ull x = a * b, y = c * p;
	long long ans = (long long) (x % p) - (long long) (y % p);
	if (ans < 0) ans += p;
	return ans;
}

int main()
{
	long long a, b, p;
	scanf("%lld%lld%lld", &a, &b, &p);
	printf("%lld\n", mul(a, b, p));
	return 0;
}