// P3367 (100 pts)
# include <cstdio>
# include <cmath>
# include <algorithm>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int fa[NR], sz[NR];

int find(int x)
{
	if (x == fa[x]) return x;
	return find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] > sz[y]) swap(x, y);
	fa[x] = y, sz[y] += sz[x];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1;
	for (int i = 1; i <= m; i++) {
		int type, x, y;
		scanf("%d%d%d", &type, &x, &y);
		if (type == 1) merge(x, y);
		if (type == 2) {
			if (find(x) == find(y)) puts("Y");
			else puts("N");
		}
	}
	return 0;
}