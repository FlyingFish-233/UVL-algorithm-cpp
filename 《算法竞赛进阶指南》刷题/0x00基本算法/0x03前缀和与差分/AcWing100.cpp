# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n;
int a[NR], d[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), d[i] = a[i] - a[i - 1];
	long long p = 0, q = 0;
	for (int i = 2; i <= n; i++) {
		if (d[i] > 0) p += d[i];
		if (d[i] < 0) q += -d[i];
	}
	printf("%lld\n", max(p, q));
	printf("%lld\n", abs(p - q) + 1);
	return 0;
}