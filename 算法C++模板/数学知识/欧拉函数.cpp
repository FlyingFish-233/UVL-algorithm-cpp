// POJ3090 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
int p[NR], v[NR];
int phi[NR];

int main()
{
	int T;
	scanf("%d", &T);
	for (int cnt = 1; cnt <= T; cnt++) {
		scanf("%d", &n);
		m = 0, memset(v, 0, sizeof(v));
		for (int i = 2; i <= n; i++) {
			if (v[i] == 0) v[i] = p[++m] = i, phi[i] = i - 1;
			for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= n; j++) {
				v[i * p[j]] = p[j];
				if (i % p[j] == 0) phi[i * p[j]] = phi[i] * p[j];
				else phi[i * p[j]] = phi[i] * (p[j] - 1);
			}
		}
		long long ans = 0;
		for (int i = 2; i <= n; i++)
			ans += phi[i];
		printf("%d %d %lld\n", cnt, n, 3 + ans * 2);
	}
	return 0;
}