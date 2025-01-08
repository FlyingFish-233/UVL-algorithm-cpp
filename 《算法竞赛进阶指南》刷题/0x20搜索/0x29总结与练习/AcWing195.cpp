# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int nxt[8][2] = {{1, 2}, {-1, -2}, {-1, 2}, {1, -2}, {2, 1}, {-2, -1}, {-2, 1}, {2, -1}};
const char t[10][10] = {"11111", "01111", "00*11", "00001", "00000"};

int dep;
char c[10][10];

int f()
{
	int val = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (c[i][j] != '*' && c[i][j] != t[i][j]) val++;
	return val;
}

bool dfs(int step, int x, int y)
{
	if (step + f() > dep) return false;
	if (f() == 0) return true;
	for (int i = 0; i < 8; i++) {
		int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
		if (x0 < 0 || x0 > 4 || y0 < 0 || y0 > 4) continue;
		swap(c[x0][y0], c[x][y]);
		if (dfs(step + 1, x0, y0)) return true;
		swap(c[x0][y0], c[x][y]);
	}
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 5; i++)
			scanf("%s", c[i]);
		int Sx, Sy;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (c[i][j] == '*') Sx = i, Sy = j;
		for (dep = 0; dep <= 15 && !dfs(0, Sx, Sy); dep++);
		if (dep > 15) printf("-1\n");
		else printf("%d\n", dep);
	}
	return 0;
}