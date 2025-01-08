// P4097 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;
const int MOD1 = 39989, MOD2 = 1e9;

struct Segment
{
	double k, b;

	double f(int x)
	{
		return k * x + b;
	}
};

int n;
Segment seg[NR];
int tree[NR << 2];

void change(int rt, int l, int r, int id)
{
	if (l == r) {
		if (tree[rt] == 0 || seg[id].f(l) > seg[tree[rt]].f(l)) tree[rt] = id;
		return;
	}
	double l1 = seg[id].f(l), l2 = seg[tree[rt]].f(l);
	double r1 = seg[id].f(r), r2 = seg[tree[rt]].f(r);
	double m1 = seg[id].f(mid), m2 = seg[tree[rt]].f(mid);
	if (l1 <= l2 && r1 <= r2) return;
	if (l1 >= l2 && r1 >= r2) {	tree[rt] = id; return; }
	if (m1 <= m2) {
		if (l1 > l2) change(ls, l, mid, id);
		if (r1 > r2) change(rs, mid + 1, r, id);
	}
	else {
		if (l1 < l2) change(ls, l, mid, tree[rt]);
		if (r1 < r2) change(rs, mid + 1, r, tree[rt]);
		tree[rt] = id;
	}
}

void modify(int rt, int l, int r, int l0, int r0, int id)
{
	if (l0 <= l && r <= r0) {
		change(rt, l, r, id);
		return;
	}
	if (l0 <= mid) modify(ls, l, mid, l0, r0, id);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, id);
}

int query(int rt, int l, int r, int x)
{
	if (l == r) return tree[rt];
	int tmp;
	if (x <= mid) tmp = query(ls, l, mid, x);
	else tmp = query(rs, mid + 1, r, x);
	double y1 = seg[tmp].f(x), y2 = seg[tree[rt]].f(x);
	if (y1 > y2) return tmp;
	if (y1 < y2) return tree[rt];
	return min(tmp, tree[rt]);
}

int main()
{
	int T, lastans = 0;
	scanf("%d", &T);
	while (T--) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			x1 = (x1 + lastans - 1) % MOD1 + 1, y1 = (y1 + lastans - 1) % MOD2 + 1;
			x2 = (x2 + lastans - 1) % MOD1 + 1, y2 = (y2 + lastans - 1) % MOD2 + 1;
			if (x1 > x2) swap(x1, x2), swap(y1, y2);
			if (x1 == x2) seg[++n] = (Segment) {0, 1.0 * max(y1, y2)};
			else {
				double save = 1.0 * (y2 - y1) / (x2 - x1);
				seg[++n] = (Segment) {save, y1 - save * x1};
			}
			modify(1, 1, MOD1, x1, x2, n);
		}
		if (type == 0) {
			int x;
			scanf("%d", &x);
			x = (x + lastans - 1) % MOD1 + 1;
			printf("%d\n", lastans = query(1, 1, MOD1, x));
		}
	}
	return 0;
}