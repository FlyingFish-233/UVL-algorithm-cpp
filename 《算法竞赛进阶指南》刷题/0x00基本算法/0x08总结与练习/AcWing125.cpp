# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

struct Array
{
	int w, s;

	bool operator < (const Array &cmp) const {
		return w + s < cmp.w + cmp.s;
	}
};

int n;
Array a[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].w, &a[i].s);
	sort(a + 1, a + n + 1);
	int ans = -2e9, w_sum = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, w_sum - a[i].s);
		w_sum += a[i].w;
	}
	printf("%d\n", ans);
	return 0;
}