# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1000 + 10;

struct Node
{
	double l, r;

	bool operator < (const Node &cmp) const {
		return r < cmp.r;
	}
};

int n, d;
Node a[NR];

int main()
{
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (y > d) {
			printf("-1\n");
			return 0;
		}
		double tmp = sqrt(d * d - y * y);
		a[i] = (Node) {x - tmp, x + tmp};
	}
	sort(a + 1, a + n + 1);
	int ans = 0;
	double now = -1e9;
	for (int i = 1; i <= n; i++)
		if (now < a[i].l) ans++, now = a[i].r;
	printf("%d\n", ans);
	return 0;
}