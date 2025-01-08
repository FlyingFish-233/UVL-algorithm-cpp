// AcWing285 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 6e3 + 10;

int n, root;
int a[NR];
vector<int> g[NR];

bool flag[NR];
int f[NR][2];

void dfs(int x)
{
	f[x][0] = 0, f[x][1] = a[x];
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		dfs(y);
		f[x][0] += max(f[y][0], f[y][1]);
		f[x][1] += f[y][0];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[y].push_back(x), flag[x] = true;
	for (int i = 1; i <= n; i++)
		if (!flag[i]) { root = i; break; }
	dfs(root);
	printf("%d\n", max(f[root][0], f[root][1]));
	return 0;
}