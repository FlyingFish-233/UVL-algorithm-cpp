# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const double eps = 1e-5;

int n, len;
double a[NR], b[NR], s[NR];

bool check(double x)
{
	for (int i = 1; i <= n; i++)
		b[i] = a[i] - x;
	for (int i = 1; i <= n; i++)
		s[i] = s[i - 1] + b[i];
	double s_min = 1e9, ans = -1e9;
	for (int i = len; i <= n; i++) {
		s_min = min(s_min, s[i - len]);
		ans = max(ans, s[i] - s_min);
	}
	return ans >= 0;
}

int main()
{
	scanf("%d%d", &n, &len);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &a[i]);
	double l = 1, r = 2000;
	while (l + eps < r) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%d\n", (int) (r * 1000));
	return 0;
}