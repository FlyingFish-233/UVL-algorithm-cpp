// P3805 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2.2e7 + 10;

int n;
char c[NR], s[NR];
int p[NR];

int main()
{
	scanf("%s", c + 1);
	int len = strlen(c + 1);
	s[n = 1] = '#';
	for (int i = 1; i <= len; i++)
		s[++n] = c[i], s[++n] = '#';
	s[0] = '$', s[n + 1] = '\0';

	int ans = 0, mid = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		if (i < r) p[i] = min(p[2 * mid - i], r - i);
		else p[i] = 1;
		while (s[i + p[i]] == s[i - p[i]]) p[i]++;
		if (r < i + p[i]) mid = i, r = i + p[i];
		ans = max(ans, p[i] - 1);
	}
	printf("%d\n", ans);
	return 0;
}