# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 200;
const int nxt[8][2] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

int m, n;
char c[NR][NR];
int Sx, Sy, Tx, Ty;

int dis[NR][NR];
queue< pair<int, int> > q;


int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++)
		scanf("%s", c[i] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (c[i][j] == 'H') Sx = i, Sy = j;
			if (c[i][j] == 'K') Tx = i, Ty = j;
		}
	memset(dis, -1, sizeof(dis));
	dis[Sx][Sy] = 0;
	q.push(make_pair(Sx, Sy));
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		if (x == Tx && y == Ty) {
			printf("%d\n", dis[x][y]);
			return 0;
		}
		for (int i = 0; i < 8; i++) {
			int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
			if (x0 < 1 || x0 > n || y0 < 1 || y0 > m) continue;
			if (dis[x0][y0] != -1 || c[x0][y0] == '*') continue;
			dis[x0][y0] = dis[x][y] + 1;
			q.push(make_pair(x0, y0));
		}
	}
	return 0;
}