# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 310;

int n, m;
int a[NR], f[NR][NR];
vector<int> g[NR];

void dfs(int x)
{
	f[x][0] = 0;
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		dfs(y);
		for (int j = m; j >= 0; j--)
			for (int k = 0; k <= j; k++)
				f[x][j] = max(f[x][j], f[x][j - k] + f[y][k]);
	}
	for (int i = m; i >= 1; i--)
		f[x][i] = f[x][i - 1] + a[x];
}

int main()
{
	scanf("%d%d", &n, &m), m++;
	for (int i = 1, x; i <= n; i++)
		scanf("%d%d", &x, &a[i]), g[x].push_back(i);
	memset(f, -0x3f, sizeof(f));
	dfs(0);
	printf("%d\n", f[0][m]);
	return 0;
}