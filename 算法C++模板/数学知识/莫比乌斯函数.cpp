// AcWing215 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

int m, v[NR], p[NR];
int miu[NR], s_miu[NR];

// |{x<=a & y<=b & gcd(x,y)=1}| = Sum(miu[i] * |{x<=a & y<=b & i|gcd(x,y)}|) = Sum(miu[i] * a/i * b/i)
int main()
{
	miu[1] = 1;
	for (int i = 2; i <= 5e4; i++) {
		if (v[i] == 0) v[i] = p[++m] = i, miu[i] = -1;
		for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= 5e4; j++) {
			v[i * p[j]] = p[j];
			if (i % p[j] == 0) miu[i * p[j]] = 0;
			else miu[i * p[j]] = -miu[i];
		}
	}
	for (int i = 1; i <= 5e4; i++)
		s_miu[i] = s_miu[i - 1] + miu[i];
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, k;
		scanf("%d%d%d", &a, &b, &k);
		a /= k, b /= k;
		if (a > b) swap(a, b);
		long long ans = 0;
		for (int i = 1, j; i <= a; i = j + 1) {
			j = (a / i == 0) ? a : min(min(a / (a / i), b / (b / i)), a);
			ans += 1ll * (s_miu[j] - s_miu[i - 1]) * (a / i) * (b / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}