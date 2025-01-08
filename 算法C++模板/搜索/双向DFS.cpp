// AcWing171 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 50, MR = (1 << 24) + 10;

int n, mid;
long long w, ans;
long long a[NR];

int len;
long long s[MR];

void dfs(int x, long long sum)
{
	if (sum > w) return;
	if (x > mid) {
		s[++len] = sum;
		return;
	}
	dfs(x + 1, sum + a[x]);
	dfs(x + 1, sum);
}

void solve(int x, long long sum)
{
	if (sum > w) return;
	if (x > n) {
		int k = upper_bound(s + 1, s + len + 1, w - sum) - s - 1;
		ans = max(ans, s[k] + sum);
		return;
	}
	solve(x + 1, sum + a[x]);
	if (ans == w) return;
	solve(x + 1, sum);
}

int main()
{
	scanf("%lld%d", &w, &n);
	mid = n / 2 + 1;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	reverse(a + 1, a + n + 1);
	dfs(1, 0);
	sort(s + 1, s + len + 1);
	len = unique(s + 1, s + len + 1) - s - 1;
	solve(mid + 1, 0);
	printf("%lld\n", ans);
	return 0;
}