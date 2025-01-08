# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 400;
const int nxt[10][2] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}, {0, -1}, {0, -2}, {-1, 0}, {-2, 0}};

int n, a[NR][16];
bool vis[NR][16][7][7][7][7];

bool check(int day, int p)
{
	return a[day][p] != 1 && a[day][p + 1] != 1 && a[day][p + 4] != 1 && a[day][p + 5] != 1;
}

bool dfs(int day, int p, int t1, int t2, int t3, int t4)
{
	if (day > n) return true;
	for (int i = 0; i < 9; i++) {
		int x = p / 4 + nxt[i][0], y = p % 4 + nxt[i][1];
		if (x < 0 || x > 2 || y < 0 || y > 2) continue;
		int p0 = x * 4 + y;
		if (!check(day, p0)) continue;
		int s1 = (p0 == 0) ? 0 : t1 + 1;
		int s2 = (p0 == 2) ? 0 : t2 + 1;
		int s3 = (p0 == 8) ? 0 : t3 + 1;
		int s4 = (p0 == 10) ? 0 : t4 + 1;
		if (s1 == 7 || s2 == 7 || s3 == 7 || s4 == 7) continue;
		if (vis[day + 1][x * 4 + y][s1][s2][s3][s4]) continue;
		vis[day + 1][x * 4 + y][s1][s2][s3][s4] = true;
		if (dfs(day + 1, x * 4 + y, s1, s2, s3, s4)) return true;
	}
	return false;
}

int main()
{
	while (scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 16; j++)
				scanf("%d", &a[i][j]);
		if (!check(1, 5)) {
			printf("0\n");
			continue;
		}
		memset(vis, false, sizeof(vis));
		printf("%d\n", dfs(2, 5, 1, 1, 1, 1));
	}
	return 0;
}