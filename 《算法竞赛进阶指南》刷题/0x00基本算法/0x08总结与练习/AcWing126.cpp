# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n, ans;
int a[NR][NR], s[NR][NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]), s[i][j] += s[i][j - 1] + a[i][j];
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++)
			for (int i = 1, now = 0; i <= n; i++)
				now = max(now, 0) + s[i][r] - s[i][l - 1], ans = max(ans, now);
	if (ans == 0) {
		ans = -2e9;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				ans = max(ans, a[i][j]);
	}
	printf("%d\n", ans);
	return 0;
}