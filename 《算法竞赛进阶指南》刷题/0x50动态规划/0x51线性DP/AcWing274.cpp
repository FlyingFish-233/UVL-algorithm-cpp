# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 200 + 10;

int n, m;
int c[MR][MR], a[NR];
int f[NR][MR][MR];

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &c[i][j]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memset(f, 0x3f, sizeof(f));
	a[0] = 3, f[0][1][2] = 0;
	for (int i = 0; i < n; i++)
		for (int x = 1; x <= m; x++)
			for (int y = 1; y <= m; y++) {
				int z = a[i], v = f[i][x][y];
				if (x == y || y == z || z == x) continue;
				f[i + 1][x][y] = min(f[i + 1][x][y], v + c[z][a[i + 1]]);
				f[i + 1][z][y] = min(f[i + 1][z][y], v + c[x][a[i + 1]]);
				f[i + 1][x][z] = min(f[i + 1][x][z], v + c[y][a[i + 1]]);
			}
	int ans = 1e9;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (i != j && j != a[n] && a[n] != i)
				ans = min(ans, f[n][i][j]);
	printf("%d\n", ans);
	return 0;
}