# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

int n;
int x[NR], y[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &x[i], &y[i]);
	sort(x + 1, x + n + 1);
	for (int i = 1; i <= n; i++)
		x[i] -= i;
	sort(x + 1, x + n + 1);
	sort(y + 1, y + n + 1);
	int mid = (n + 1) / 2, ans = 0;
	for (int i = 1; i <= n; i++)
		ans += abs(x[i] - x[mid]) + abs(y[i] - y[mid]);
	printf("%d\n", ans);
	return 0;
}