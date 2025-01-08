# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 4e3 + 10;

int n, m;
int a[NR], f[NR][2];

void dp()
{
	for (int i = 2; i <= n; i++)
		for (int j = m; j >= 0; j--) {
			f[j][0] = max(f[j][0], f[j][1]);
			if (j >= 1) f[j][1] = max(f[j - 1][0], f[j - 1][1] + a[i]);
		}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	memset(f, -0x3f, sizeof(f));
	f[0][0] = f[1][1] = 0, dp();
	int save = max(f[m][0], f[m][1]);

	memset(f, -0x3f, sizeof(f));
	f[1][1] = a[1], dp();
	printf("%d\n", max(save, f[m][1]));
	return 0;
}