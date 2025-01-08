# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

struct Array
{
	int w, d;
	bool operator < (const Array &cmp) const {
		return w > cmp.w;
	}
};

int n;
Array a[NR];

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
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &a[i].w, &a[i].d);
		sort(a + 1, a + n + 1);
		for (int i = 0; i <= 1e4; i++)
			fa[i] = i;
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (find(a[i].d) > 0)
				merge(find(a[i].d), find(a[i].d) - 1), ans += a[i].w;
		printf("%d\n", ans);
	}
	return 0;
}