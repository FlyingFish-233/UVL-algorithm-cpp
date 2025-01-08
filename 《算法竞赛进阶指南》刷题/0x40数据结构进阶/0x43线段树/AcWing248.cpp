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
	long long x, y1, y2, d;

	bool operator < (const Scanline &cmp) const {
		if (x != cmp.x) return x < cmp.x;
		return d > cmp.d;
	}
};

int n, m, w, h;
Scanline a[NR];
long long t[NR];

int id(long long x)
{
	return lower_bound(t + 1, t + m + 1, x) - t;
}

struct Node
{
	int max, tag;
};

Node tree[NR << 2];

void pushdown(int rt)
{
	if (tree[rt].tag == 0) return;
	tree[ls].max += tree[rt].tag;
	tree[rs].max += tree[rt].tag;
	tree[ls].tag += tree[rt].tag;
	tree[rs].tag += tree[rt].tag;
	tree[rt].tag = 0;
}

void pushup(int rt)
{
	tree[rt].max = max(tree[ls].max, tree[rs].max);
}

void modify(int rt, int l, int r, int l0, int r0, int delta)
{
	if (l0 <= l && r <= r0) {
		tree[rt].max += delta;
		tree[rt].tag += delta;
		return;
	}
	pushdown(rt);
	if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, delta);
	pushup(rt);
}

int main()
{
	while (scanf("%d%d%d", &n, &w, &h) != EOF) {
		for (int i = 1; i <= n; i++) {
			long long x, y, c;
			scanf("%lld%lld%lld", &x, &y, &c);
			t[i] = y, t[i + n] = y + h - 1;
			a[i] = (Scanline) {x, y, y + h - 1, c};
			a[i + n] = (Scanline) {x + w - 1, y, y + h - 1, -c};
		}
		n <<= 1;
		sort(t + 1, t + n + 1);
		m = unique(t + 1, t + n + 1) - t - 1;
		sort(a + 1, a + n + 1);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			modify(1, 1, m, id(a[i].y1), id(a[i].y2), a[i].d);
			ans = max(ans, tree[1].max);
		}
		printf("%d\n", ans);
	}
	return 0;
}