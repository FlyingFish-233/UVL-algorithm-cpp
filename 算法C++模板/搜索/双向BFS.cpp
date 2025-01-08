// AcWing177 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1000;
const int nxt[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct Node
{
	int x, y, s;
};

int n, m;
char c[NR][NR];

Node z[2];
queue<Node> q[2];
int f[NR][NR];

bool check(int x, int y, int t)
{
	if (x < 1 || y < 1 || x > n ||  y > m || c[x][y] == 'X') return false;
	if (abs(x - z[0].x) + abs(y - z[0].y) <= 2 * t) return false;
	if (abs(x - z[1].x) + abs(y - z[1].y) <= 2 * t) return false;
	return true;
}

bool bfs(int op, int t, int v)
{
	while (!q[op].empty() && q[op].front().s < t * v) {
		int x = q[op].front().x, y = q[op].front().y, s = q[op].front().s;
		q[op].pop();
		if (!check(x, y, t)) continue;
		for (int i = 0; i < 4; i++) {
			int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
			if (!check(x0, y0, t)) continue;
			if (f[x0][y0] == -1) {
				f[x0][y0] = op;
				q[op].push((Node) {x0, y0, s + 1});
			}
			else if (f[x0][y0] != op) return true;
		}
	}
	return false;
}

int solve()
{
	memset(f, -1, sizeof(f));
	while (!q[0].empty()) q[0].pop();
	while (!q[1].empty()) q[1].pop();
	int tmp = -1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (c[i][j] == 'Z') z[++tmp] = (Node) {i, j, 0};
			if (c[i][j] == 'M') f[i][j] = 0, q[0].push((Node) {i, j, 0});
			if (c[i][j] == 'G') f[i][j] = 1, q[1].push((Node) {i, j, 0});
		}
	for (int t = 1; !q[0].empty() || !q[1].empty(); t++)
		if (bfs(0, t, 3) || bfs(1, t, 1)) return t;
	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%s", c[i] + 1);
		printf("%d\n", solve());
	}
	return 0;
}