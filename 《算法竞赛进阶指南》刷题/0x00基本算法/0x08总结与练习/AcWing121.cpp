# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1000 + 10;

int target, n;
int a[NR], b[NR];
int m, t[NR];
int s[NR][NR];

int getId(int x)
{
	return upper_bound(t + 1, t + m + 1, x) - t - 1;
}

bool check(int mid)
{
	for (int x1 = 1, x2 = 1; x2 <= m; x2++) {
		while (t[x1] < t[x2] - mid + 1) x1++;
		for (int y1 = 1, y2 = 1; y2 <= m; y2++) {
			while (t[y1] < t[y2] - mid + 1) y1++;
			if (s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] >= target)
				return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d%d", &target, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i], &b[i]);
		t[++m] = a[i], t[++m] = b[i];
	}
	sort(t + 1, t + m + 1);
	m = unique(t + 1, t + m + 1) - t - 1;
	for (int i = 1; i <= n; i++)
		s[getId(a[i])][getId(b[i])]++;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	int l = 1, r = t[m], ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}