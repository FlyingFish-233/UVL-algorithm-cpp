# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e3 + 10;

int n;
int a[NR], b[NR];
int f[NR][NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) {
		int f_max = 0;
		for (int j = 1; j <= n; j++) {
			f[i][j] = f[i - 1][j];
			if (a[i] == b[j]) f[i][j] = max(f[i][j], f_max + 1);
			if (b[j] < a[i]) f_max = max(f_max, f[i][j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, f[n][i]);
	printf("%d\n", ans);
	return 0;
}