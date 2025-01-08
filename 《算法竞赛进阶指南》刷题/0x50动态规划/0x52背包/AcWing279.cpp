# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 4e3 + 10;
const long long mod = 2147483648;

int n;
long long f[NR];

int main()
{
	scanf("%d", &n);
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			(f[j] += f[j - i]) %= mod;
	printf("%lld\n", f[n] - 1);
	return 0;
}