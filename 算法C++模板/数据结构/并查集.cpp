// P3367 (100 pts)
# include <cstdio>
# include <cmath>
# include <algorithm>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int fa[NR];

int find(int x)
{
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	fa[find(x)] = find(y);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
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