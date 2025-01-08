# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10;

int n, r;
int s[NR][NR];

int main()
{
	scanf("%d%d", &n, &r);
	int x_max = r, y_max = r;
	for (int i = 1; i <= n; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		s[++x][++y] += w;
		x_max = max(x_max, x);
		y_max = max(y_max, y);
	}
	for (int i = 1; i <= x_max; i++)
		for (int j = 1; j <= y_max; j++)
			s[i][j] += s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
	int ans = 0;
	for (int i = r; i <= x_max; i++)
		for (int j = r; j <= y_max; j++)
			ans = max(ans, s[i][j] - s[i - r][j] - s[i][j - r] + s[i - r][j - r]);
	printf("%d\n", ans);
	return 0;
}