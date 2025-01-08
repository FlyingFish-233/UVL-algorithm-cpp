# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n;
int op[NR], a[NR];
int f[2][NR][NR];

int main()
{
	memset(f[0], 0x3f, sizeof(f[0]));
	memset(f[1], -0x3f, sizeof(f[1]));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		char c; int x;
		cin >> c >> x;
		op[i + n] = op[i] = (c == 'x');
		f[0][i + n][i + n] = f[0][i][i] = x;
		f[1][i + n][i + n] = f[1][i][i] = x;
	}
	for (int len = 2; len <= n; len++)
		for  (int l = 1; l <= (n << 1) - len + 1; l++) {
			int r = l + len - 1;
			for (int i = l; i < r; i++)
			for (int t1 = 0; t1 <= 1; t1++)
			for (int t2 = 0; t2 <= 1; t2++) {
				int save = (op[i + 1] == 0) ? f[t1][l][i] + f[t2][i + 1][r] : f[t1][l][i] * f[t2][i + 1][r];
				f[0][l][r] = min(f[0][l][r], save), f[1][l][r] = max(f[1][l][r], save);
			}
		}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, f[1][i][i + n - 1]);
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		if (ans == f[1][i][i + n - 1])
			printf("%d ", i);
	puts("");
	return 0;
}