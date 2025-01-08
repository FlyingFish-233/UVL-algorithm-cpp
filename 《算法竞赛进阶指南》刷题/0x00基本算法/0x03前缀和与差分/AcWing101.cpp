# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

int n, pos, h_max, m;
int a[NR], d[NR];
bool g[NR][NR];

int main()
{
	scanf("%d%d%d%d", &n, &pos, &h_max, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (g[x][y]) continue;
		g[x][y] = g[y][x] = true;
		if (x > y) swap(x, y);
		d[x + 1]++, d[y]--;
	}
	for (int i = 1; i <= n; i++)
		a[i] = a[i - 1] + d[i];
	for (int i = 1; i <= n; i++)
		printf("%d\n", h_max - a[i]);
	return 0;
}