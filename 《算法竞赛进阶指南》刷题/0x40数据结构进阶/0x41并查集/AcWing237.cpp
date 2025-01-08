# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e6 + 10;

int n;
int a[NR], b[NR], c[NR];

int m, t[NR];

int id(int x)
{
	return lower_bound(t + 1, t + m + 1, x) - t;
}

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
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n), m = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
			t[++m] = a[i], t[++m] = b[i];
		}
		sort(t + 1, t + m + 1);
		m = unique(t + 1, t + m + 1) - t - 1;

		for (int i = 1; i <= m; i++)
			fa[i] = i;
		for (int i = 1; i <= n; i++)
			if (c[i] == 1) merge(id(a[i]), id(b[i]));
		bool flag = true;
		for (int i = 1; i <= n; i++)
			if (c[i] == 0 && find(id(a[i])) == find(id(b[i]))) {
				flag = false;
				break;
			}
		if (flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}