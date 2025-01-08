# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 500 + 10;
const int nxt[3][4][3] = {{{2, -2, 0}, {2, 1, 0}, {1, 0, -2}, {1, 0, 1}},
						  {{1, -1, 0}, {1, 1, 0}, {0, 0, -1}, {0, 0, 2}},
						  {{0, -1, 0}, {0, 2, 0}, {2, 0, -1}, {2, 0, 1}}};

struct Node
{
	int sta, x, y;
};

int n, m;
char c[NR][NR];
int f[3][NR][NR];
Node s, t;
queue<Node> q;

bool check(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && c[x][y] != '#';
}

bool check(int sta, int x, int y)
{
	if (sta == 0) return check(x, y) && c[x][y] != 'E';
	if (sta == 1) return check(x, y) && check(x, y + 1);
	if (sta == 2) return check(x, y) && check(x + 1, y);
	return false;
}

int main()
{
	while (scanf("%d%d", &n, &m) && n && m) {
		for (int i = 1; i <= n; i++)
			scanf("%s", c[i] + 1);
		s.sta = t.sta = -1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (s.sta == -1 && c[i][j] == 'X') {
					s = (Node) {0, i, j};
					if (c[i][j + 1] == 'X') s.sta = 1;
					if (c[i + 1][j] == 'X') s.sta = 2;
				}
				if (t.sta == -1 && c[i][j] == 'O')
					t = (Node) {0, i, j};
			}
		memset(f, 0x3f, sizeof(f));
		f[s.sta][s.x][s.y] = 0;
		while (!q.empty()) q.pop();
		q.push(s);
		while (!q.empty() && f[t.sta][t.x][t.y] > 1e9) {
			int sta = q.front().sta, x = q.front().x, y = q.front().y;
			q.pop();
			for (int i = 0; i < 4; i++) {
				int sta0 = nxt[sta][i][0], x0 = x + nxt[sta][i][1], y0 = y + nxt[sta][i][2];
				if (!check(sta0, x0, y0)) continue;
				if (f[sta0][x0][y0] < 1e9) continue;
				f[sta0][x0][y0] = f[sta][x][y] + 1;
				q.push((Node) {sta0, x0, y0});
			}
		}
		if (f[t.sta][t.x][t.y] > 1e9) printf("Impossible\n");
		else printf("%d\n", f[t.sta][t.x][t.y]);
	}
	return 0;
}