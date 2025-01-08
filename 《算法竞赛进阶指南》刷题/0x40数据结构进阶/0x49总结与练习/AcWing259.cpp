# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1210;

int n, m, p1, p2;
int fa[NR], sz[NR];
bool used[NR];

int len, a[NR], b[NR];
int f[NR][NR];
int tot, save[NR];

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
	while (scanf("%d%d%d", &m, &p1, &p2) && !(m == 0 && p1 == 0 && p2 == 0)) {
		n = p1 + p2;
		for (int i = 1; i <= 2 * n; i++)
			fa[i] = i;
		bool flag = true;
		while (m--) {
			int x, y; char c[5];
			scanf("%d%d%s", &x, &y, c);
			if (c[0] == 'n') {
				if (find(x) == find(y)) flag = false;
				else merge(x, y + n), merge(x + n, y);
			}
			else {
				if (find(x) == find(y + n)) flag = false;
				else merge(x, y), merge(x + n, y + n);
			}
		}
		if (!flag) { printf("no\n"); continue; }

		memset(sz, 0, sizeof(sz)), len = 0;
		memset(used, false, sizeof(used));
		for (int i = 1; i <= n; i++)
			sz[find(i)]++;
		for (int i = 1; i <= n; i++)
			if (find(i) != find(i + n) && !used[find(i)]) {
				used[find(i)] = used[find(i + n)] = true;
				a[++len] = find(i), b[len] = find(i + n);
			}

		memset(f, 0, sizeof(f)), f[0][0] = 1;
		for (int i = 1; i <= len; i++)
			for (int j = 0; j <= n; j++) {
				if (j >= sz[a[i]]) f[i][j] += f[i - 1][j - sz[a[i]]];
				if (j >= sz[b[i]]) f[i][j] += f[i - 1][j - sz[b[i]]];
				if (f[i][j] > 1) f[i][j] = 2;
			}
		if (f[len][p1] != 1) { printf("no\n"); continue; }

		tot = 0;
		for (int i = len; i >= 1; i--)
			if (f[i - 1][p1 - sz[a[i]]]) p1 -= sz[a[i]], save[++tot] = a[i];
			else if (f[i - 1][p1 - sz[b[i]]]) p1 -= sz[b[i]], save[++tot] = b[i];
		for (int i = 1; i <= n; i++) {
			bool flag = false;
			for (int j = 1; j <= tot; j++)
				if (find(i) == save[j]) { flag = true; break; }
			if (flag) printf("%d\n", i);
		}
		printf("end\n");
	}
	return 0;
}