# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Array
{
	int u, v, w;
	bool operator < (const Array &cmp) const {
		return w > cmp.w;
	}
};

int n, m;
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
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
	sort(a + 1, a + m + 1);
	for (int i = 1; i <= n * 2; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++)
		if (find(a[i].u) == find(a[i].v)) return printf("%d\n", a[i].w), 0;
		else merge(a[i].u, a[i].v + n), merge(a[i].u + n, a[i].v);
	printf("0\n");
	return 0;
}