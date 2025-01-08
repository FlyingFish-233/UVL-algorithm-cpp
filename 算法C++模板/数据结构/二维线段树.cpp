// P3437 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)

using namespace std;

const int NR = 4e3 + 10;

int n, m;

struct InTree
{
	int val[NR], tag[NR];

	void modify(int rt, int l, int r, int l0, int r0, int delta) {
		val[rt] = max(val[rt], delta);
		if (l0 <= l && r <= r0) {
			tag[rt] = max(tag[rt], delta);
			return;
		}
		int mid = (l + r) >> 1;
		if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
		if (mid < r0) modify(rs, mid + 1, r, l0, r0, delta);
	}

	int getans(int rt, int l, int r, int l0, int r0) {
		if (l0 <= l && r <= r0) return val[rt];
		int mid = (l + r) >> 1, ans = tag[rt];
		if (l0 <= mid) ans = max(ans, getans(ls, l, mid, l0, r0));
		if (mid < r0) ans = max(ans, getans(rs, mid + 1, r, l0, r0));
		return ans;
	}
};

struct OutTree
{
	InTree val[NR], tag[NR];

	void modify(int rt, int l, int r, int l0, int r0, int y1, int y2, int delta) {
		val[rt].modify(1, 1, m, y1, y2, delta);
		if (l0 <= l && r <= r0) {
			tag[rt].modify(1, 1, m, y1, y2, delta);
			return;
		}
		int mid = (l + r) >> 1;
		if (l0 <= mid) modify(ls, l, mid, l0, r0, y1, y2, delta);
		if (mid < r0) modify(rs, mid + 1, r, l0, r0, y1, y2, delta);
	}

	int getans(int rt, int l, int r, int l0, int r0, int y1, int y2) {
		if (l0 <= l && r <= r0) return val[rt].getans(1, 1, m, y1, y2);
		int mid = (l + r) >> 1, ans = tag[rt].getans(1, 1, m, y1, y2);
		if (l0 <= mid) ans = max(ans, getans(ls, l, mid, l0, r0, y1, y2));
		if (mid < r0) ans = max(ans, getans(rs, mid + 1, r, l0, r0, y1, y2));
		return ans;
	}
};

OutTree tree;

int main()
{
	int T;
	scanf("%d%d%d", &n, &m, &T);
	while (T--) {
		int a, b, c, x, y;
		scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
		int tmp = tree.getans(1, 1, n, x + 1, x + a, y + 1, y + b);
		tree.modify(1, 1, n, x + 1, x + a, y + 1, y + b, tmp + c);
	}
	printf("%d\n", tree.getans(1, 1, n, 1, n, 1, m));
	return 0;
}