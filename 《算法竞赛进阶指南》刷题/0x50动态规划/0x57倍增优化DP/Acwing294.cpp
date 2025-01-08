# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n1, n2, len1, len2;
char s1[NR], s2[NR];
long long f[NR][50];

int main()
{
	while (scanf("%s%d%s%d", s2, &n2, s1, &n1) != EOF) {
		len1 = strlen(s1), len2 = strlen(s2);
		memset(f, 0, sizeof(f));
		bool flag = true;
		for (int i = 0; i < len1; i++) if (flag)
			for (int j = 0, x = i; j < len2; j++) {
				int cnt = 0;
				while (s1[x] != s2[j]) {
					x = (x + 1) % len1;
					if (++cnt == len1) { flag = false; break; }
				}
				if (!flag) break;
				x = (x + 1) % len1;
				f[i][0] += cnt + 1;
			}
		if (!flag) { printf("0\n"); continue; }
		for (int j = 1; j <= 30; j++)
			for (int i = 0; i < len1; i++)
				f[i][j] = f[i][j - 1] + f[(i + f[i][j - 1]) % len1][j - 1];
		long long x = 0, ans = 0;
		for (int i = 30; i >= 0; i--)
			if (x + f[x % len1][i] <= n1 * len1)
				x += f[x % len1][i], ans += 1 << i;
		printf("%lld\n", ans / n2);
	}
	return 0;
}