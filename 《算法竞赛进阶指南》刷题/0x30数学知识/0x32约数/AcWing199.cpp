# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int main()
{
	long long n, k, ans;
	scanf("%lld%lld", &n, &k);
	ans = n * k;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = (k / i == 0) ? n : min(k / (k / i), n);
		ans -= (k / i) * (j - i + 1) * (i + j) / 2;
	}
	printf("%lld\n", ans);
	return 0;
}