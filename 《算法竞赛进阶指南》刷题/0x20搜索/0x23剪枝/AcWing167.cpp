# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100;

int n, sum, ans;
int a[NR];
bool used[NR];

bool dfs(int x, int now, int stt)
{
	if (x > sum / ans) return true;
	if (now == ans) return dfs(x + 1, 0, 1);
	for (int i = stt; i <= n; i++) {
		if (used[i] || now + a[i] > ans) continue;
		used[i] = true;
		if (dfs(x, now + a[i], i + 1)) return true;
		used[i] = false;
		while (i + 1 <= n && a[i + 1] == a[i]) i++;
		if (now == 0 || now + a[i] == ans) return false;
	}
	return false;
}

int main()
{
	while (scanf("%d", &n) && n) {
		sum = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum += a[i];
			ans = max(ans, a[i]);
		}
		sort(a + 1, a + n + 1);
		reverse(a + 1, a + n + 1);
		for ( ; ans <= sum; ans++) {
			if (sum % ans != 0) continue;
			memset(used, false, sizeof(used));
			if (dfs(1, 0, 1)) break;
		}
		printf("%d\n", ans);
	}
	return 0;
}