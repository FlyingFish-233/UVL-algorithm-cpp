# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

int miu[NR], s_miu[NR];
bool flag[NR];

int main()
{
	for (int i = 1; i <= 5e4; i++)
		miu[i] = 1, flag[i] = true;
	flag[1] = false;
	for (int i = 2; i <= 5e4; i++) if (flag[i]) {
		miu[i] = -1;
		for (int j = 2; i * j <= 5e4; j++)
			flag[i * j] = false, miu[i * j] *= (j % i == 0) ? 0 : -1;
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