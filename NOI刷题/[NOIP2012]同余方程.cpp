// P1082 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

typedef long long LL;

using namespace std;

void exgcd(LL a, LL b, LL &x, LL &y)
{
	if (b == 0) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}

int main()
{
	LL a, b, x, y;
	scanf("%lld%lld", &a, &b);
	exgcd(a, b, x, y);
	printf("%lld\n", (x + b) % b);
	return 0;
}