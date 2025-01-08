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

struct Node
{
	long long sum, tag;
};

int n, m;
int a[NR];
Node tree[NR << 2];

void pushdown(int rt, int l, int r)
{
	if (tree[rt].tag == 0) return;
	tree[ls].sum += (mid - l + 1) * tree[rt].tag;
	tree[rs].sum += (r - mid) * tree[rt].tag;
	tree[ls].tag += tree[rt].tag;
	tree[rs].tag += tree[rt].tag;
	tree[rt].tag = 0;
}

void pushup(int rt)
{
	tree[rt].sum = tree[ls].sum + tree[rs].sum;
}

void build(int rt, int l, int r)
{
	if (l == r) { tree[rt].sum = a[l]; return; }
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(rt);
}

void modify(int rt, int l, int r, int l0, int r0, int delta)
{
	if (l0 <= l && r <= r0) {
		tree[rt].sum += 1ll * (r - l + 1) * delta;
		tree[rt].tag += delta;
		return;
	}
	pushdown(rt, l, r);
	if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, delta);
	pushup(rt);
}

long long getsum(int rt, int l, int r, int l0, int r0)
{
	if (l0 <= l && r <= r0) return tree[rt].sum;
	pushdown(rt, l, r);
	long long ans = 0;
	if (l0 <= mid) ans += getsum(ls, l, mid, l0, r0);
	if (mid < r0) ans += getsum(rs, mid + 1, r, l0, r0);
	pushup(rt);
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	build(1, 1, n);
	while (m--) {
		char c; int l, r, d;
		cin >> c;
		if (c == 'C') scanf("%d%d%d", &l, &r, &d), modify(1, 1, n, l, r, d);
		if (c == 'Q') scanf("%d%d", &l, &r), printf("%lld\n", getsum(1, 1, n, l, r));
	}
	return 0;
}