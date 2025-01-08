# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 310;

int n;
int a[NR], s[NR];
int f[NR][NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++)
		f[i][i] = 0;
	for (int len = 2; len <= n; len++)
		for (int l = 1; l <= n - len + 1; l++) {
			int r = l + len - 1;
			for (int i = l; i < r; i++)
				f[l][r] = min(f[l][r], f[l][i] + f[i + 1][r] + s[r] - s[l - 1]);
		}
	printf("%d\n", f[1][n]);
	return 0;
}