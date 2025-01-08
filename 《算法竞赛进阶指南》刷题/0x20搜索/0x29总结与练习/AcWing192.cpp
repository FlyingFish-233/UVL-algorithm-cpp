# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 100, lim = 30;
int nxt[3][4][3] = {{{-2, 0, 1}, {1, 0, 1}, {0, -2, 2}, {0, 1, 2}},
					{{-1, 0, 0}, {2, 0, 0}, {0, 1, 1}, {0, -1, 1}},
					{{-1, 0, 2}, {1, 0, 2}, {0, -1, 0}, {0, 2, 0}}};

struct Node
{
	int x, y, type;
};

int dis[NR][NR][3];
queue<Node> q;

void init()
{
	memset(dis, -1, sizeof(dis));
	dis[3][3][0] = 0;
	q.push((Node) {3, 3, 0});
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y, t = q.front().type; q.pop();
		for (int i = 0; i < 4; i++) {
			int x0 = x + nxt[t][i][0], y0 = y + nxt[t][i][1], t0 = nxt[t][i][2];
			if (x0 < 0 || y0 < 0 || x0 > lim || y0 > lim || dis[x0][y0][t0] != -1) continue;
			dis[x0][y0][t0] = dis[x][y][t] + 1;
			q.push((Node) {x0, y0, t0});
		}
	}
}

int main()
{
	init(); 
	int x, y, t; char c;
	while (cin >> c >> x >> y) {
		if (c == 'U') t = 0;
		if (c == 'V') t = 1;
		if (c == 'H') t = 2;
		x += 3, y += 3;
		if (x <= lim && y <= lim) {
			printf("%d\n", dis[x][y][t]);
			continue;
		}
		int x0 = x / 3 * 3, y0 = y / 3 * 3;
		if (x0 == 3) {
			printf("%d\n", dis[x][y - (y0 - 6)][t] + (y0 - 6) / 3 * 2);
			continue;
		}
		if (y0 == 3) {
			printf("%d\n", dis[x - (x0 - 6)][y][t] + (x0 - 6) / 3 * 2);
			continue;
		}
		printf("%d\n", dis[x - (x0 - 6)][y - (y0 - 6)][t] + (x0 - 6) / 3 * 2 + (y0 - 6) / 3 * 2);
	}
	return 0;
}