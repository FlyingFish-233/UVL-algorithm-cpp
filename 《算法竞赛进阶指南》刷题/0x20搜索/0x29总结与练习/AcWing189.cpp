# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 110;
const int nxt[10][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

int n, m, Sx, Sy, ans;
char c[NR][NR];

int dis[NR][NR];
queue < pair<int, int> > q;

int main()
{
	scanf("%d%d%d%d", &n, &m, &Sx, &Sy);
	for (int j = m; j >= 1; j--)
		for (int i = 1; i <= n; i++)
			cin >> c[i][j];
	memset(dis, -1, sizeof(dis));
	dis[Sx][Sy] = 0;
	q.push(make_pair(Sx, Sy));
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		ans = max(ans, dis[x][y]);
		for (int i = 0; i < 8; i++) {
			int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
			if (x0 < 1 || x0 > n || y0 < 1 || y0 > m) continue;
			if (c[x0][y0] == '*' || dis[x0][y0] != -1) continue;
			dis[x0][y0] = dis[x][y] + 1;
			q.push(make_pair(x0, y0));
		}
	}
	printf("%d\n", ans);
	return 0;
}