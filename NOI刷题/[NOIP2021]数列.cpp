// P7961 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int PR = 998244353;

int n, m, K;
int v[110][40], c[40][40], cnt[40];
int f[110][40][40][40];

/*
f[i][j][k][sta]表示v[0]~v[i-1], a[1]~a[j], S = sta * 2^i + S', S'中1的个数为k
每次转移选了t个v[i]:
	f[i + 1][j + t][k + (sta + t) % 2][(sta + t) / 2] += f[i][j][k][sta] * v[i]^t * c[n - j][t]
*/

int main()
{
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 0, x; i <= m; i++) {
		scanf("%d", &x), v[i][0] = 1;
		for (int j = 1; j <= n; j++)
			v[i][j] = 1ll * v[i][j - 1] * x % PR;
	}
	for (int i = 0; i <= n; i++)
		c[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % PR;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= 6; j++)
			cnt[i] += i >> j & 1;
			
	f[0][0][0][0] = 1;
	for (int i = 0; i <= m; i++)
	for (int j = 0; j <= n; j++)
	for (int k = 0; k <= min(j, K); k++)
	for (int sta = 0; sta <= j / 2; sta++) // 选j个2^(i-1)时sta最大, 此时sta=j/2
	for (int t = 0; j + t <= n; t++)
		(f[i + 1][j + t][k + (sta + t) % 2][(sta + t) / 2] += 1ll * f[i][j][k][sta] * v[i][t] % PR * c[n - j][t] % PR) %= PR;
	int ans = 0;
	for (int k = 0; k <= K; k++)
		for (int sta = 0; sta <= n / 2; sta++)
			if (k + cnt[sta] <= K) (ans += f[m + 1][n][k][sta]) %= PR;
	printf("%d\n", ans);
 	return 0;
}

