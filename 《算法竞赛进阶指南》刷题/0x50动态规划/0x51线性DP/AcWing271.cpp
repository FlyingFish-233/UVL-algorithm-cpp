# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 31;

int a[10], b[10];
long long f[NR][NR][NR][NR][NR];

int main()
{
	int k;
	while (scanf("%d", &k) && k) {
		memset(b, 0, sizeof(b));
		for (int i = 1; i <= k; i++)
			scanf("%d", &b[i]);
		memset(f, 0, sizeof(f));
		f[0][0][0][0][0] = 1;
		for (a[1] = 0; a[1] <= b[1]; a[1]++)
		for (a[2] = 0; a[2] <= min(b[2], a[1]); a[2]++)
		for (a[3] = 0; a[3] <= min(b[3], a[2]); a[3]++)
		for (a[4] = 0; a[4] <= min(b[4], a[3]); a[4]++)
		for (a[5] = 0; a[5] <= min(b[5], a[4]); a[5]++)
			for (int i = 1; i <= 5; i++) if (a[i] < b[i] && (i == 1 || a[i - 1] > a[i])) {
				long long t = f[a[1]][a[2]][a[3]][a[4]][a[5]];
				a[i]++, f[a[1]][a[2]][a[3]][a[4]][a[5]] += t, a[i]--;
			}
		printf("%lld\n", f[b[1]][b[2]][b[3]][b[4]][b[5]]);
	}
	return 0;
}