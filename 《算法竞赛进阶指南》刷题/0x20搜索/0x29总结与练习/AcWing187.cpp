# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100;

int n, dep;
int a[NR];
int up[NR], down[NR];

bool cmp(int x, int y)
{
	return x > y;
}

bool dfs(int x, int len1, int len2)
{
	if (len1 + len2 > dep) return false;
	if (x > n) return true;
	int k, save;

	k = upper_bound(up + 1, up + len1 + 1, a[x], cmp) - up;
	if (k != len1 + 1) {
		save = up[k], up[k] = a[x];
		if (dfs(x + 1, len1, len2)) return true;
		up[k] = save;
	}
	else {
		up[len1 + 1] = a[x];
		if (dfs(x + 1, len1 + 1, len2)) return true;
	}

	k = upper_bound(down + 1, down + len2 + 1, a[x]) - down;
	if (k != len2 + 1) {
		save = down[k], down[k] = a[x];
		if (dfs(x + 1, len1, len2)) return true;
		down[k] = save;
	}
	else {
		down[len2 + 1] = a[x];
		if (dfs(x + 1, len1, len2 + 1)) return true;
	}
	return false;
}

int main()
{
	while (scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (dep = 1; !dfs(1, 0, 0); dep++);
		printf("%d\n", dep);
	}
	return 0;
}