// P1115 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 2e5 + 10;

int n;
int a[NR];
int f[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int ans = -2e9;
	for (int i = 1; i <= n; i++)
		f[i] = max(f[i - 1], 0) + a[i], ans = max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}