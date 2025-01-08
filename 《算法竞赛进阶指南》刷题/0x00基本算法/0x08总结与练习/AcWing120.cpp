# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

int n, lim_max;
int a[NR], d[NR], lim[NR];

bool check(int x)
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (x >= a[i]) sum += (min(x, lim[i]) - a[i]) / d[i] + 1;
	return sum & 1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		lim_max = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d", &a[i], &lim[i], &d[i]), lim_max = max(lim_max, lim[i]);
		int l = 1, r = lim_max, pos = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) r = mid - 1, pos = mid;
			else l = mid + 1;
		}
		if (pos == -1) {
			printf("There's no weakness.\n");
			continue;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans += (pos >= a[i] && pos <= lim[i] && (pos - a[i]) % d[i] == 0);
		printf("%d %d\n", pos, ans);
	}
	return 0;
}