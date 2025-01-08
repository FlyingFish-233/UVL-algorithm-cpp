// AcWing91 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 30, MR = 1 << 20;

int n;
int g[NR][NR];
int f[MR][NR];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i <= n - 1; i++)
		for (int j = 0; j <= n - 1; j++)
			scanf("%d", &g[i][j]);
	const int lim = (1 << n) - 1;
	memset(f, 0x3f, sizeof(f));
	f[1][0] = 0;
	for (int sta = 0; sta < lim; sta++) 
		for (int i = 0; i <= n - 1; i++) if (sta >> i & 1) 
			for (int j = 0; j <= n - 1; j++) if (!(sta >> j & 1))
				f[sta | (1 << j)][j] = min(f[sta | (1 << j)][j], f[sta][i] + g[i][j]);
	printf("%d\n", f[lim][n - 1]);
	return 0;
}