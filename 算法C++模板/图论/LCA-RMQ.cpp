// P3379 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e6 + 10;

int n, m, root;
vector<int> g[NR];
int tot, dfn[NR], dep[NR];
int lg2[NR], pos[NR][30];

void build(int x, int dad)
{
	pos[++tot][0] = x, dfn[x] = tot;
	dep[x] = dep[dad] + 1;
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (y != dad) build(y, x), pos[++tot][0] = x;
	}
}

void init()
{
	for (int i = 2; i <= tot; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int j = 1; (1 << j) <= tot; j++)
		for (int i = 1; i + (1 << j) - 1 <= tot; i++) {
			int x = pos[i][j - 1], y = pos[i + (1 << (j - 1))][j - 1];
			pos[i][j] = (dep[x] < dep[y]) ? x : y;
		}
}

int query(int l, int r)
{
	if (l > r) swap(l, r);
	int k = lg2[r - l + 1], x = pos[l][k], y = pos[r - (1 << k) + 1][k];
	return (dep[x] < dep[y]) ? x : y;
}

int main()
{
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	build(root, 0), init();
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", query(dfn[x], dfn[y]));
	}
	return 0;
}