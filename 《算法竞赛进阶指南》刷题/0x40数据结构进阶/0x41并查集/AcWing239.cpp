# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <map>

using namespace std;

const int NR = 1e4 + 10;

int n, m;
int a[NR], b[NR], c[NR];
map<int, int> mp;

int fa[NR << 1];

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
	scanf("%d%d", &n, &m), n = 0;
	for (int i = 1; i <= m; i++) {
		char str[5];
		scanf("%d%d%s", &a[i], &b[i], str), a[i]--;
		c[i] = (str[0] == 'o');
		if (mp.count(a[i]) == 0) mp[a[i]] = ++n;
		if (mp.count(b[i]) == 0) mp[b[i]] = ++n;
		a[i] = mp[a[i]], b[i] = mp[b[i]];
	}
	for (int i = 1; i <= (n << 1); i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++)
		if (c[i] == 0) {
			if (find(a[i]) == find(b[i] + n))
				return printf("%d\n", i - 1), 0;
			merge(a[i], b[i]);
			merge(a[i] + n, b[i] + n);
		}
		else {
			if (find(a[i]) == find(b[i]))
				return printf("%d\n", i - 1), 0;
			merge(a[i], b[i] + n);
			merge(a[i] + n, b[i]);
		}
	printf("%d\n", m);
	return 0;
}