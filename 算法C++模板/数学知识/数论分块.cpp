// P2261 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

long long s(int x)
{
	return 1ll * x * (x + 1) / 2;
}

// 答案为n*k - Sum(i*[k/i]) {1<=i<=k}
// Lemma: 对所有x<=i<=[k/[k/x]], [k/i]全部相等
int main()
{
	long long n, k, sum = 0;
	scanf("%lld%lld", &n, &k);
	for (int i = 1, j; i <= n; i = j + 1) {
		j = (k / i == 0) ? n : min(k / (k / i), n);
		sum += (k / i) * (s(j) - s(i - 1));
	}
	printf("%lld\n", n * k - sum);
	return 0;
}