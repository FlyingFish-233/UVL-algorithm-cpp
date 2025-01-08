# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 2e4 + 10;

struct Scanline
{
	double x, y1, y2; int d;

	bool operator < (const Scanline &cmp) const {
		if (x != cmp.x) return x < cmp.x;
		return d > cmp.d;
	}
};

int n, m;
Scanline a[NR];
double t[NR];

int id(double x)
{
	return lower_bound(t + 1, t + m + 1, x) - t;
}

struct Node
{
	int cnt;
	double len;
};

Node tree[NR << 3];

void modify(int rt, int l, int r, int l0, int r0, int delta)
{
	if (l0 <= l && r <= r0) {
		tree[rt].cnt += delta;
		if (tree[rt].cnt > 0) tree[rt].len = t[r + 1] - t[l];
		else tree[rt].len = tree[ls].len + tree[rs].len;
		return;
	}
	if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, delta);
	if (tree[rt].cnt > 0) tree[rt].len = t[r + 1] - t[l];
	else tree[rt].len = tree[ls].len + tree[rs].len;
}

int main()
{
	for (int save = 1; scanf("%d", &n) && n; save++) {
		for (int i = 1; i <= n; i++) {
			double x1, y1, x2, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			t[i] = y1, t[i + n] = y2;
			a[i] = (Scanline) {x1, y1, y2, 1};
			a[i + n] = (Scanline) {x2, y1, y2, -1};
		}
		n <<= 1;
		sort(t + 1, t + n + 1);
		m = unique(t + 1, t + n + 1) - t - 1;
		sort(a + 1, a + n + 1);
		double ans = 0;
		for (int i = 1; i <= n; i++) {
			modify(1, 1, m, id(a[i].y1), id(a[i].y2) - 1, a[i].d);
			if (i < n) ans += tree[1].len * (a[i + 1].x - a[i].x);
		}
		printf("Test case #%d\n", save);
		printf("Total explored area: %.2f \n\n", ans);
	}
	return 0;
}