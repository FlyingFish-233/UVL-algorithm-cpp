# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n, a[NR];
long long sum, s[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), sum += a[i];
	int target = sum / n;
	for (int i = 1; i <= n; i++)
		s[i] = s[i - 1] + a[i] - target;
	sort(s + 1, s + n + 1);
	long long mid = s[(n + 1) / 2], ans = 0;
	for (int i = 1; i <= n; i++)
		ans += abs(s[i] - mid);
	printf("%lld\n", ans);
	return 0;
}