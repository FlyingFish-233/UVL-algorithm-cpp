# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1000 + 10;
const int three[10] = {1, 3, 9, 27, 81, 243, 729};

char c[NR][NR];

void dfs(int n, int x, int y)
{
	if (n == 1) {
		c[x][y] = 'X';
		return;
	}
	dfs(n - 1, x, y);
	dfs(n - 1, x, y + 2 * three[n - 2]);
	dfs(n - 1, x + three[n - 2], y + three[n - 2]);
	dfs(n - 1, x + 2 * three[n - 2], y);
	dfs(n - 1, x + 2 * three[n - 2], y + 2 * three[n - 2]);
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (n == -1) break;
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= three[n - 1]; i++)
			for (int j = 1; j <= three[n - 1]; j++)
				c[i][j] = ' ';
		dfs(n, 1, 1);
		for (int i = 1; i <= three[n - 1]; i++)
			printf("%s\n", c[i] + 1);
		puts("-");
	}
	return 0;
}