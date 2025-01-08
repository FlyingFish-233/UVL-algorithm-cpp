# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 60;

int n, m;
int a[NR][NR];
int f[NR][NR][NR][NR];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	memset(f, -0x3f, sizeof(f));
	f[1][1][1][1] = 0;
	for (int i = 2; i <= n + m - 1; i++)
	for (int x1 = 1; x1 <= n; x1++)
	for (int x2 = 1; x2 <= n; x2++) {
		int y1 = i + 1 - x1, y2 = i + 1 - x2;
		if (y1 < 1 || y1 > m || y2 < 1 || y2 > m) continue;
		if (x1 == x2 && y1 == y2 && !(x1 == n && y1 == m)) continue;
		f[x1][y1][x2][y2] = max(f[x1][y1][x2][y2], f[x1 - 1][y1][x2 - 1][y2] + a[x1][y1] + a[x2][y2]);
		f[x1][y1][x2][y2] = max(f[x1][y1][x2][y2], f[x1 - 1][y1][x2][y2 - 1] + a[x1][y1] + a[x2][y2]);
		f[x1][y1][x2][y2] = max(f[x1][y1][x2][y2], f[x1][y1 - 1][x2 - 1][y2] + a[x1][y1] + a[x2][y2]);
		f[x1][y1][x2][y2] = max(f[x1][y1][x2][y2], f[x1][y1 - 1][x2][y2 - 1] + a[x1][y1] + a[x2][y2]);
	}
	printf("%d\n", f[n][m][n][m]);
	return 0;
}