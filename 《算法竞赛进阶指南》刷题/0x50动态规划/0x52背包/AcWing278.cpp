# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 1e4 + 10;

int n, m;
int a[NR], f[MR];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= a[i]; j--)
			f[j] += f[j - a[i]];
	printf("%d\n", f[m]);
	return 0;
}