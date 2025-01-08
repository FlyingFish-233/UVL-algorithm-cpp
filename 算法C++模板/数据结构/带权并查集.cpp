// AcWing238 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e4 + 10;

int fa[NR], d[NR], sz[NR];
// d[x]表示x到fa[x]的距离

int find(int x)
{
	if (fa[x] == x) return x;
	int root = find(fa[x]);
	d[x] += d[fa[x]];
	return fa[x] = root;
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	fa[x] = y, d[x] = sz[y];
	sz[y] += sz[x];
}

int main()
{
	for (int i = 1; i <= 3e4; i++)
		fa[i] = i, sz[i] = 1;
	int T;
	scanf("%d", &T);
	while (T--) {
		char c;
		int x, y;
		cin >> c >> x >> y;
		if (c == 'M') merge(y, x);
		if (c == 'C') {
			if (find(x) != find(y)) { printf("-1\n"); continue; }
			printf("%d\n", abs(d[x] - d[y]) - 1);
		}
	}
	return 0;
}