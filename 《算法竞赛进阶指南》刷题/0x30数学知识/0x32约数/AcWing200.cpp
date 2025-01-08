# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int a, b, c, d;
int m, p[NR], v[NR];

int count(int x, int y)
{
	int cnt = 0;
	while (x % y == 0) x /= y, cnt++;
	return cnt;
}

int solve(int x)
{
	int a0 = count(a, x), b0 = count(b, x), c0 = count(c, x), d0 = count(d, x);
	if (a0 > c0 && b0 < d0 && c0 == d0) return 1;
	if (a0 > c0 && b0 == d0 && c0 <= d0) return 1;
	if (a0 == c0 && b0 < d0 && c0 <= d0) return 1;
	if (a0 == c0 && b0 == d0 && c0 <= d0) return d0 - c0 + 1;
	return 0;
}

int main()
{
	for (int i = 2; i <= 1e5; i++) {
		if (v[i] == 0) v[i] = p[++m] = i;
		for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= 1e5; j++)
			v[i * p[j]] = p[j];
	}

	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &a, &c, &b, &d);
		int ans = 1, now = d;
		for (int i = 1; i <= m && 1ll * p[i] * p[i] <= d && ans; i++)
			if (d % p[i] == 0) {
				while (now > 1 && now % p[i] == 0) now /= p[i];
				ans *= solve(p[i]);
			}
		if (now > 1) ans *= solve(now);
		printf("%d\n", ans);
	}
	return 0;
}