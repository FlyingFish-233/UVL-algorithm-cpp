# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 1e5 + 10;

int n, m;
int a[NR], b[NR];
int f[MR], cnt[MR];

int main()
{
	while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		memset(f, false, sizeof(f));
		f[0] = true;
		for (int i = 1; i <= n; i++) {
			memset(cnt, 0, sizeof(cnt));
			for (int j = a[i]; j <= m; j++)
				if (!f[j] && f[j - a[i]] && cnt[j - a[i]] < b[i])
					f[j] = true, cnt[j] = cnt[j - a[i]] + 1;
		}
		int ans = 0;
		for (int i = 1; i <= m; i++)
			ans += f[i];
		printf("%d\n", ans);
	}
	return 0;
}