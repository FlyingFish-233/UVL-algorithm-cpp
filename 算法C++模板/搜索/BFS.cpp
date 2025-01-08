// AcWing173 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e3 + 10;
const int nxt[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m;
char c[NR][NR];
int f[NR][NR];
queue< pair<int, int> > q;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", c[i] + 1);
	memset(f, -1, sizeof(f));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (c[i][j] == '1') q.push(make_pair(i, j)), f[i][j] = 0;
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
			if (x0 < 1 || x0 > n || y0 < 1 || y0 > m) continue;
			if (f[x0][y0] != -1) continue;
			f[x0][y0] = f[x][y] + 1;
			q.push(make_pair(x0, y0));
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			printf("%d ", f[i][j]);
		puts("");
	}
	return 0;
}