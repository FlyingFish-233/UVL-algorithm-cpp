# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int a[NR], op[NR], b[NR];
int fa[NR], last;

void init(int x)
{
	for (int i = 1; i <= x; i++)
		fa[i] = i;
}

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	fa[find(x)] = find(y);
}

bool check(int x)
{
	init(3 * n);
	for (int i = 1; i <= m; i++) {
		if (a[i] == x || b[i] == x) continue;
		if (op[i] == 0) {
			if (find(a[i]) == find(b[i] + n) || find(a[i]) == find(b[i] + n * 2)) {
				last = max(last, i);
				return false;
			}
			merge(a[i], b[i]);
			merge(a[i] + n, b[i] + n);
			merge(a[i] + 2 * n, b[i] + 2 * n);
		}
		else {
			if (find(a[i]) == find(b[i]) || find(a[i]) == find(b[i] + n * 2)) {
				last = max(last, i);
				return false;
			}
			merge(a[i], b[i] + n);
			merge(a[i] + n, b[i] + 2 * n);
			merge(a[i] + 2 * n, b[i]);
		}
	}
	return true;
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; i++) {
			char c;
			scanf("%d%c%d", &a[i], &c, &b[i]);
			a[i]++, b[i]++;
			if (c == '=') op[i] = 0;
			if (c == '<') op[i] = 1;
			if (c == '>') op[i] = 1, swap(a[i], b[i]);
		}
		int cnt = 0, pos = 0; last = 0;
		for (int i = 1; i <= n; i++)
			if (check(i)) cnt++, pos = i - 1;
		if (cnt == 0) printf("Impossible\n");
		if (cnt == 1) printf("Player %d can be determined to be the judge after %d lines\n", pos, last);
		if (cnt > 1) printf("Can not determine\n");
	}
	return 0;
}