# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n, m;
int v[NR], p[NR];
int cnt[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		if (v[i] == 0) v[i] = p[++m] = i;
		for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= n; j++)
			v[i * p[j]] = p[j];
	}
	for (int i = 1; i <= m; i++)
		for (long long w = p[i]; w <= n; w *= p[i])
			cnt[i] += n / w;
	for (int i = 1; i <= m; i++)
		printf("%d %d\n", p[i], cnt[i]);
	return 0;
}