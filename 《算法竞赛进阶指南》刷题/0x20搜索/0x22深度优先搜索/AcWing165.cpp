# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20;

int n, w, a[NR];
int ans = 2e9, box[NR];

void dfs(int x, int cnt)
{
	if (cnt >= ans) return;
	if (x > n) { ans = cnt; return; }
	for (int i = 1; i <= cnt; i++)
		if (a[x] + box[i] <= w) {
			box[i] += a[x];
			dfs(x + 1, cnt);
			box[i] -= a[x];
		}
	box[cnt + 1] += a[x];
	dfs(x + 1, cnt + 1);
	box[cnt + 1] -= a[x];
}

int main()
{
	scanf("%d%d", &n, &w);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	reverse(a + 1, a + n + 1);
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}