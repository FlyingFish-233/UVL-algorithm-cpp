# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10, MR = 1e5;
const int INF = 0x3f3f3f3f;

int l, r;
int m, v[NR], p[NR];
bool flag[NR];
int len, a[NR];

int main()
{
	for (int i = 2; i <= MR; i++) {
		if (v[i] == 0) v[i] = p[++m] = i;
		for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= MR; j++)
			v[i * p[j]] = p[j];
	}
	while (scanf("%d%d", &l, &r) != EOF) {
		int k = upper_bound(p + 1, p + m + 1, (int) sqrt(r)) - p - 1;
		memset(flag, true, sizeof(flag));
		if (l == 1) flag[0] = false;
		for (int i = 1; i <= k; i++)
			for (int j = max(2., ceil(1.0 * l / p[i])); j <= r / p[i]; j++)
				flag[p[i] * j - l] = false;
		len = 0;
		for (int i = 0; i <= r - l; i++)
			if (flag[i]) a[++len] = i + l;
		int d_min = INF, t1, d_max = -INF, t2;
		for (int i = 2; i <= len; i++) {
			if (a[i] - a[i - 1] < d_min) d_min = a[t1 = i] - a[i - 1];
			if (a[i] - a[i - 1] > d_max) d_max = a[t2 = i] - a[i - 1];
		}
		if (d_min == INF) printf("There are no adjacent primes.\n");
		else printf("%d,%d are closest, %d,%d are most distant.\n", a[t1 - 1], a[t1], a[t2 - 1], a[t2]);
	}
	return 0;
}