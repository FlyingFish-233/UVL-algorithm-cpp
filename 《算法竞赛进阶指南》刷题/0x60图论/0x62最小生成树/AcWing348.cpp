# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1000 + 10;
const double eps = 1e-6;

int n;
int a[NR], b[NR], c[NR];
double h[NR][NR], len[NR][NR];
double g[NR][NR];

bool flag[NR];
double dis[NR];

bool check(double mid)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = h[i][j] - mid * len[i][j];
	memset(flag, false, sizeof(flag));
	for (int i = 1; i <= n; i++) dis[i] = 1e9;
	double ans = 0; dis[1] = 0;
	for (int i = 1; i <= n; i++) {
		int x = 0;
		for (int j = 1; j <= n; j++)
			if (!flag[j] && (x == 0 || dis[j] < dis[x])) x = j;
		flag[x] = true, ans += dis[x];
		for (int y = 1; y <= n; y++)
			if (!flag[y]) dis[y] = min(dis[y], g[x][y]);
	}
	return ans <= 0;
}

int main()
{
	while (scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				h[i][j] = abs(c[i] - c[j]), len[i][j] = sqrt((a[i] - a[j]) * (a[i] - a[j]) + (b[i] - b[j]) * (b[i] - b[j]));
		double l = 0, r = 1e7, ans = 0;
		while (r - l > eps) {
			double mid = (l + r) / 2;
			if (check(mid)) ans = r = mid;
			else l = mid;
		}
		printf("%.3f\n", ans);
	}
	return 0;
}