# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e3 + 10;

int n, m;
int a[NR], b[NR];
long long f[NR][NR];

long long dp()
{
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= m; i++)
		f[0][i] = 0;
	for (int i = 1; i <= n; i++) {
		long long f_min = 1e17;
		for (int j = 1; j <= m; j++) {
			f_min = min(f_min, f[i - 1][j]);
			f[i][j] = f_min + abs(a[i] - b[j]);
		}
	}
	long long ans = 1e17;
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[n][i]);
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - b - 1;
	long long t1 = dp();
	reverse(b + 1, b + m + 1);
	long long t2 = dp();
	printf("%lld\n", min(t1, t2));
	return 0;
}