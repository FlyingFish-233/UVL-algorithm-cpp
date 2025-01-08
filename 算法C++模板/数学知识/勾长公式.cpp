// AcWing271 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int k;
int a[10], g[30][30];

long long gcd(long long x, long long y)
{
	return (y == 0) ? x : gcd(y, x % y);
}

int main()
{
	while (scanf("%d", &k) && k) {
		for (int i = 1; i <= k; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= a[i]; j++) {
				g[i][j] = a[i] - j;
				for (int tmp = i + 1; tmp <= k && a[tmp] >= j; tmp++) g[i][j]++;
			}
		long long s1 = 1, s2 = 1; int now = 0;
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= a[i]; j++) {
				s1 *= ++now, s2 *= g[i][j] + 1;
				long long save = gcd(s1, s2);
				s1 /= save, s2 /= save;
			}
		printf("%lld\n", s1);
	}
	return 0;
}