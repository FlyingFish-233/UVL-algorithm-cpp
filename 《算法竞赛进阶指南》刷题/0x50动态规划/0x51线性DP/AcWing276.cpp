# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20, MR = 250;

struct Node
{
	int i, l, r, j, t1, t2;
};

int n, m, k;
int a[NR][NR], s[NR][NR];
int f[NR][NR][NR][MR][2][2];
Node pre[NR][NR][NR][MR][2][2];

void update(int i, int l, int r, int j, int t1, int t2, int l0, int r0)
{
	if (f[i][l][r][j][t1][t2] < f[i - 1][l0][r0][j - (r - l + 1)][t1][t2] + s[i][r] - s[i][l - 1]) {
		f[i][l][r][j][t1][t2] = f[i - 1][l0][r0][j - (r - l + 1)][t1][t2] + s[i][r] - s[i][l - 1];
		pre[i][l][r][j][t1][t2] = (Node) {i - 1, l0, r0, j - (r - l + 1), t1, t2};
	}
}

bool flag[NR][NR];

void mark(Node now)
{
	if (now.j == 0) return;
	for (int i = now.l; i <= now.r; i++)
		flag[now.i][i] = true;
	mark(pre[now.i][now.l][now.r][now.j][now.t1][now.t2]);
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]), s[i][j] = s[i][j - 1] + a[i][j];
	memset(f, -0x3f, sizeof(f));

	for (int i = 1; i <= n; i++)
	for (int l = 1; l <= m; l++)
	for (int r = l; r <= m; r++)
	for (int j = r - l + 1; j <= k; j++) {
		if (j == r - l + 1) f[i][l][r][j][0][0] = s[i][r] - s[i][l - 1];
		for (int l0 = l; l0 <= r; l0++)
		for (int r0 = l0; r0 <= r; r0++)
			update(i, l, r, j, 0, 0, l0, r0);
			
		f[i][l][r][j][1][0] = f[i][l][r][j][0][0], pre[i][l][r][j][1][0] = (Node) {i, l, r, j, 0, 0};
		for (int l0 = 1; l0 <= l; l0++)
		for (int r0 = l; r0 <= r; r0++)
			update(i, l, r, j, 1, 0, l0, r0);

		f[i][l][r][j][0][1] = f[i][l][r][j][0][0], pre[i][l][r][j][0][1] = (Node) {i, l, r, j, 0, 0};
		for (int l0 = l; l0 <= r; l0++)
		for (int r0 = r; r0 <= m; r0++)
			update(i, l, r, j, 0, 1, l0, r0);

		if (f[i][l][r][j][1][1] < f[i][l][r][j][1][0]) f[i][l][r][j][1][1] = f[i][l][r][j][1][0], pre[i][l][r][j][1][1] = (Node) {i, l, r, j, 1, 0};
		if (f[i][l][r][j][1][1] < f[i][l][r][j][0][1]) f[i][l][r][j][1][1] = f[i][l][r][j][0][1], pre[i][l][r][j][1][1] = (Node) {i, l, r, j, 0, 1};
		for (int l0 = 1; l0 <= l; l0++)
		for (int r0 = r; r0 <= m; r0++)
			update(i, l, r, j, 1, 1, l0, r0);
	}

	int ans = 0; Node now;
	for (int i = 1; i <= n; i++)
	for (int l = 1; l <= m; l++)
	for (int r = l; r <= m; r++)
		if (ans < f[i][l][r][k][1][1])
			ans = f[i][l][r][k][1][1], now = (Node) {i, l, r, k, 1, 1};
	printf("Oil : %d\n", ans);
	mark(now);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (flag[i][j]) printf("%d %d\n", i, j);
	return 0;
}