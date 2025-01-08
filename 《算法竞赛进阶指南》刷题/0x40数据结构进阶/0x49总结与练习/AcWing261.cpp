# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 5e4 + 10;

struct Node
{
	int max, lmax, rmax, tag;
};

int n, m;
Node tree[NR << 2];

void pushDown(int rt, int l, int r)
{
	if (tree[rt].tag == 0) return;
	if (tree[rt].tag == 1) {
		tree[ls].max = tree[ls].lmax = tree[ls].rmax = 0;
		tree[rs].max = tree[rs].lmax = tree[rs].rmax = 0;
	}
	if (tree[rt].tag == 2) {
		tree[ls].max = tree[ls].lmax = tree[ls].rmax = mid - l + 1;
		tree[rs].max = tree[rs].lmax = tree[rs].rmax = r - mid;
	}
	tree[ls].tag = tree[rs].tag = tree[rt].tag;
	tree[rt].tag = 0;
}

void pushUp(int rt, int l, int r)
{
	tree[rt].lmax = tree[ls].lmax;
	if (tree[ls].lmax == mid - l + 1) tree[rt].lmax += tree[rs].lmax;
	tree[rt].rmax = tree[rs].rmax;
	if (tree[rs].rmax == r - mid) tree[rt].rmax += tree[ls].rmax;
	tree[rt].max = max(max(tree[ls].max, tree[rs].max), tree[ls].rmax + tree[rs].lmax);
}

void build(int rt, int l, int r)
{
	tree[rt].max = tree[rt].lmax = tree[rt].rmax = r - l + 1;
	if (l == r) return;
	build(ls, l, mid);
	build(rs, mid + 1, r);
}

void modify(int rt, int l, int r, int l0, int r0, int x)
{
	if (l0 <= l && r <= r0) {
		if (x == 1)  tree[rt].max = tree[rt].lmax = tree[rt].rmax = 0;
		else tree[rt].max = tree[rt].lmax = tree[rt].rmax = r - l + 1;
		tree[rt].tag = x;
		return;
	}
	pushDown(rt, l, r);
	if (l0 <= mid) modify(ls, l, mid, l0, r0, x);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, x);
	pushUp(rt, l, r);
}

int query(int rt, int l, int r, int x)
{
	if (tree[rt].max < x) return 0;
	pushDown(rt, l, r);
	if (tree[ls].max >= x) return query(ls, l, mid, x);
	if (tree[ls].rmax + tree[rs].lmax >= x) return mid - tree[ls].rmax + 1;
	if (tree[rs].max >= x) return query(rs, mid + 1, r, x);
	pushUp(rt, l, r);
	return 0;
}

int main()
{
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	while (m--) {
		int op, x, d;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &d);
			x = query(1, 1, n, d);
			if (x != 0) modify(1, 1, n, x, x + d - 1, 1);
			printf("%d\n", x);
		}
		else {
			scanf("%d%d", &x, &d);
			modify(1, 1, n, x, x + d - 1, 2);
		}
	}
	return 0;
}