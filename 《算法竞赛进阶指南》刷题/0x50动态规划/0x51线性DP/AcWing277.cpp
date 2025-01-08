# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 50, MR = 5e3 + 10;

struct Array
{
	int x, id;
	bool operator < (const Array &cmp) const {
		return x > cmp.x;
	}
};

int n, m;
Array a[NR];
int p[NR], s[NR];
int f[NR][MR], pre[NR][MR][2];
int ans[NR];

void getans(int x, int y)
{
	if (x == 0 && y == 0) return;
	if (x == pre[x][y][0]) {
		for (int i = 1; i <= x; i++)
			ans[i]++;
	}
	else {
		for (int i = pre[x][y][0] + 1; i <= x; i++)
			ans[i]++;
	}
	getans(pre[x][y][0], pre[x][y][1]);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i].x), a[i].id = i;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		s[i] = s[i - 1] + a[i].x, p[a[i].id] = i;
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= m; j++) {
			f[i][j] = f[i][j - i], pre[i][j][0] = i, pre[i][j][1] = j - i;
			for (int k = 0; k < i; k++)
				if (f[i][j] > f[k][j - (i - k)] + k * (s[i] - s[k])) {
					f[i][j] = f[k][j - (i - k)] + k * (s[i] - s[k]);
					pre[i][j][0] = k, pre[i][j][1] = j - (i - k);
				}
		}
	printf("%d\n", f[n][m]);
	getans(n, m);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[p[i]]);
	puts("");
	return 0;
}