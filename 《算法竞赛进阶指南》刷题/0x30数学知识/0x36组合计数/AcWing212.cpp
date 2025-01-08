# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10, mod = 1e9 + 9;

int n, a[NR];
int factory[NR];
bool flag[NR];

int fastPow(int a, int b)
{
	int ans = 1;
	for (int i = b; i; i >>= 1, a = 1ll * a * a % mod)
		if (i & 1) ans = 1ll * ans * a % mod;
	return ans;
}

int main()
{
	factory[0] = 1;
	for (int i = 1; i <= 1e5; i++)
		factory[i] = 1ll * factory[i - 1] * i % mod;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		memset(flag, false, sizeof(flag));
		int ans = 1, tot = 0;
		for (int i = 1; i <= n; i++) {
			if (flag[i]) continue;
			int cnt = 0; tot++;
			for (int j = i; !flag[j]; j = a[j])
				flag[j] = true, cnt++;
			if (cnt > 1) ans = 1ll * ans * fastPow(cnt, cnt - 2) % mod;
			ans = 1ll * ans * fastPow(factory[cnt - 1], mod - 2) % mod;
		}
		ans = 1ll * ans * factory[n - tot] % mod;
		printf("%d\n", ans);
	}
	return 0;
}