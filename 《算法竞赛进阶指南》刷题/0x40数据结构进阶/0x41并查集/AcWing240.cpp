# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 150000 + 10;

int n, m, ans;
int fa[NR];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	fa[find(x)] = find(y);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n * 3; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (x > n || y > n) continue;
		if (op == 2 && x == y) continue;
		if (op == 1 && find(x) != find(y + n) && find(x) != find(y + n * 2))
			ans++, merge(x, y), merge(x + n, y + n), merge(x + n * 2, y + n * 2);
		if (op == 2 && find(x) != find(y) && find(x) != find(y + n))
			ans++, merge(x, y + 2 * n), merge(x + n, y), merge(x + n * 2, y + n);
	}
	printf("%d\n", m - ans);
	return 0;
}