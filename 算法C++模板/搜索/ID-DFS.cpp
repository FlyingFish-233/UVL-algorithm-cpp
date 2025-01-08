// AcWing170 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n, ans;
int a[NR];
bool vis[NR];

bool dfs(int x)
{
	if (x > ans) return a[ans] == n;
	for (int i = x - 1; i >= 1; i--)
		for (int j = i; j >= 1; j--) {
			if (vis[a[i] + a[j]] || a[i] + a[j] > n || a[i] + a[j] <= a[x - 1]) continue;
			a[x] = a[i] + a[j];
			vis[a[x]] = true;
			if (dfs(x + 1)) return true;
			vis[a[x]] = false;
		}
	return false;
}

int main()
{
	while (scanf("%d", &n) && n) {
		for (ans = 1; ans <= n; ans++) {
			memset(vis, false, sizeof(vis));
			vis[a[1] = 1] = true;
			if (dfs(2)) {
				for (int i = 1; i <= ans; i++)
					printf("%d ", a[i]);
				puts("");
				break;
			}
		}
	}
	return 0;
}